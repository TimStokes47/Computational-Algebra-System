#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include "maths/Matrix3x3.h"
#include "maths/Matrix2x2.h"
#include "maths/FloatMatrix4x4.h"
#include "graphics/Shader.h"
#include "maths/Vec3.h"
#include "graphics/Camera2D.h"
#include "Input.h"
#include "graphics/Renderer.h"
#include "graphics/Axis.h"

#include "expressionParsing/grammar.h"
#include "expressionParsing/expressionScanner.h"
#include "Animator.h"

void inputMatrix4x4Value(Matrix4x4& matrix);
void inputMatrix3x3Value(Matrix3x3& matrix, std::vector<Vec3>& eigenvector);
void inputMatrix2x2Value(Matrix2x2& matrix, std::vector<Vec2>& eigenvectors);

GLFWwindow* initialise();

int main() {
	GLFWwindow* window = initialise();
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);*/
	
	unsigned int squareVertexArray = Renderer2D::generateUnitSquare();
	unsigned int grid2DVertexArray = Renderer2D::generateGrid();
	unsigned int cubeVertexArray = Renderer3D::generateUnitCube();

	Shader vertexShader3DAffine("shaders/Vertex Shader 3D Affine.vs", GL_VERTEX_SHADER);
	Shader vertexShader2DAffine("shaders/Vertex Shader 2D Affine.vs", GL_VERTEX_SHADER);
	Shader vertexShader2DLinear("shaders/Vertex Shader 2D Linear.vs", GL_VERTEX_SHADER);
	Shader vertexShader3DLinear("shaders/Vertex Shader 3D Linear.vs", GL_VERTEX_SHADER);

	Shader fragmentShader2D("shaders/Fragment Shader 2D.fs", GL_FRAGMENT_SHADER);
	Shader fragmentShader3D("shaders/Fragment Shader 3D.fs", GL_FRAGMENT_SHADER);

	ShaderProgram program2DAffine;
	program2DAffine.linkShader(vertexShader2DAffine);
	program2DAffine.linkShader(fragmentShader2D);
	program2DAffine.compile();

	ShaderProgram program2DLinear;
	program2DLinear.linkShader(vertexShader2DLinear);
	program2DLinear.linkShader(fragmentShader2D);
	program2DLinear.compile();

	ShaderProgram program3DAffine;
	program3DAffine.linkShader(vertexShader3DAffine);
	program3DAffine.linkShader(fragmentShader3D);
	program3DAffine.compile();

	ShaderProgram program3DLinear;
	program3DLinear.linkShader(vertexShader3DLinear);
	program3DLinear.linkShader(fragmentShader3D);
	program3DLinear.compile();

	ShaderProgram* program = &program2DAffine;

	Camera* camera = new Camera2D({0.0f, 0.0f, 10.0f});
	Axis2D::generateVertexArrays();

	bool is2D = true;
	bool isLinear = false;
	bool displayEigenvectors = false;
	bool displayBox = true;
	bool displayGrid = false;

	Matrix4x4 model = Matrix4x4::identity();

	std::chrono::time_point<std::chrono::system_clock> lastTime = std::chrono::system_clock::now();
	Matrix4x4 transformation4x4 = Matrix4x4::identity();
	Matrix3x3 transformation3x3 = Matrix3x3::identity();
	Matrix2x2 transformation2x2 = Matrix2x2::identity();
	Matrix3x3 identity3x3 = Matrix3x3::identity();
	Matrix4x4 identity4x4 = Matrix4x4::identity();
	Matrix2x2 identity2x2 = Matrix2x2::identity();
	std::vector<Vec2> eigenvectors2x2 = transformation2x2.calculateEigenvectors();
	std::vector<Vec3> eigenvectors3x3;

	while (!glfwWindowShouldClose(window)) {
		std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
		std::chrono::duration<float, std::ratio<1, 1>> elapsedTime = (time - lastTime);
		lastTime = time;

		camera->update(elapsedTime.count());

		model = Matrix4x4::translate(0.0f, 0.0f, 0.0f);

		program->attach();
		program->setUniformMatrix4x4("u_Model", identity4x4);
		program->setUniformMatrix4x4("u_View", camera->getLookAtMatrix());
		program->setUniformMatrix4x4("u_Projection", camera->getProjectionMatrix());
		

		program->setUniformVec4("u_Colour", { 0.3f, 0.2f, 0.8f, 1.0f });
		Animator2x2::updateAnimation(transformation2x2, elapsedTime.count());
		Animator3x3::updateAnimation(transformation3x3, elapsedTime.count());
		Animator4x4::updateAnimation(transformation4x4, elapsedTime.count());

		if (is2D && isLinear) {
			program->setUniformMatrix2x2("u_Transform", transformation2x2);
		}
		else if (!is2D && !isLinear) {
			program->setUniformMatrix4x4("u_Transform", transformation4x4);
		}
		else {
			program->setUniformMatrix3x3("u_Transform", transformation3x3);
		}

		program->setUniformMatrix4x4("u_Model", model);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (displayBox) {
			if (is2D) {
				glBindVertexArray(squareVertexArray);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			}
			else {
				glBindVertexArray(cubeVertexArray);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			}
		}

		if (is2D && isLinear) {
			program->setUniformMatrix2x2("u_Transform", identity2x2);
		}
		else if (!is2D && !isLinear) {
			program->setUniformMatrix4x4("u_Transform", identity4x4);
		}
		else {
			program->setUniformMatrix3x3("u_Transform", identity3x3);
		}

		if (displayEigenvectors) {
			glLineWidth(1.5f);
			program->setUniformVec4("u_Colour", { 0.8f, 0.2f, 0.3f, 1.0f });
			for (Vec2 eigenvector : eigenvectors2x2) {
				glBindVertexArray(Renderer2D::generateRay(eigenvector));
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
			}
			glLineWidth(1.0f);
		}

		program->setUniformVec4("u_Colour", { 0.7f, 0.7f, 0.8f, 1.0f });
		glBindVertexArray(Axis2D::getXAxis());
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
		//program->setUniformVec4("u_Colour", { 0.2f, 0.2f, 0.8f, 1.0f });
		glBindVertexArray(Axis2D::getYAxis());
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);

		if (!is2D) {
			glBindVertexArray(Axis2D::getZAxis());
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
		}

		program->setUniformVec4("u_Colour", { 0.3f, 0.3f, 0.3f, 0.1f });

		if (displayGrid) {
			if (is2D && isLinear) {
				program->setUniformMatrix2x2("u_Transform", transformation2x2);
			}
			else if (!is2D && !isLinear) {
				program->setUniformMatrix4x4("u_Transform", transformation4x4);
			}
			else {
				program->setUniformMatrix3x3("u_Transform", transformation3x3);
			}
		}

		if (is2D) {
			glBindVertexArray(Axis2D::getXAxis());
			for (int i = 0; i < 200; i++) {
				model = Matrix4x4::translate(0.0f, (float)(i - 100), 0.0f);

				program->setUniformMatrix4x4("u_Model", model);
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
			}
			glBindVertexArray(Axis2D::getYAxis());
			for (int i = 0; i < 200; i++) {
				model = Matrix4x4::translate((float)(i - 100), 0.0f, 0.0f);

				program->setUniformMatrix4x4("u_Model", model);
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
			}
		}
		else {
			glBindVertexArray(Axis2D::getXAxis());
			for (int i = 0; i < 200; i++) {
				model = Matrix4x4::translate(0.0f, 0.0f, (float)(i - 100));

				program->setUniformMatrix4x4("u_Model", model);
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
			}
			glBindVertexArray(Axis2D::getZAxis());
			for (int i = 0; i < 200; i++) {
				model = Matrix4x4::translate((float)(i - 100), 0.0f, 0.0f);

				program->setUniformMatrix4x4("u_Model", model);
				glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
			}
		}

		if (!is2D) {
			//program->setUniformVec4("u_Colour", { 0.2f, 0.8f, 0.2f, 1.0f });
			glBindVertexArray(Axis2D::getZAxis());
			glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{

			//ImGui::ShowDemoWindow();
			ImGui::Begin("Set Transformation");
			
			if (is2D) {
				if (isLinear) {
					inputMatrix2x2Value(transformation2x2, eigenvectors2x2);
					if (ImGui::Button("Affine")) {
						isLinear = false;
						program = &program2DAffine;
					}
					
					if (ImGui::Button("Animate")) {
						Animator2x2::startAnimation(Matrix2x2::identity(), transformation2x2, transformation2x2, 5.0f);
					}
					ImGui::Checkbox("Display Eigenvectors", &displayEigenvectors);
				}
				else {
					inputMatrix3x3Value(transformation3x3, eigenvectors3x3);
					if (ImGui::Button("Linear")) {
						isLinear = true;
						program = &program2DLinear;
					}
					if (ImGui::Button("Animate")) {
						Animator3x3::startAnimation(Matrix3x3::identity(), transformation3x3, transformation3x3, 5.0f);
					}
				}
			}
			else {
				if (isLinear) {
					inputMatrix3x3Value(transformation3x3, eigenvectors3x3);
					if (ImGui::Button("Affine")) {
						isLinear = false;
						program = &program3DAffine;
					}
					if (ImGui::Button("Animate")) {
						Animator3x3::startAnimation(Matrix3x3::identity(), transformation3x3, transformation3x3, 5.0f);
					}

				}
				else {
					inputMatrix4x4Value(transformation4x4);
					if (ImGui::Button("Linear")) {
						isLinear = true;
						program = &program3DLinear;
					}
					if (ImGui::Button("Animate")) {
						Animator4x4::startAnimation(Matrix4x4::identity(), transformation4x4, transformation4x4, 5.0f);
					}
				}
			}

			ImGui::Checkbox("Display Box", &displayBox);
			ImGui::Checkbox("Transform Grid", &displayGrid);
			
			if (Parsing::Variable::s_map.size() > 0) {
				ImGui::Separator();
			}
			for (auto& [character, value] : Parsing::Variable::s_map) {
				if (ImGui::SliderFloat(std::string(1, character).c_str(), &value, -20.0f, 20.0f)) {
					transformation2x2.generateFloatData();
					transformation3x3.generateFloatData();
					transformation4x4.generateFloatData();
				}
			}

			if (is2D) {
				if (ImGui::Button("3D")) {
					is2D = false;
					delete camera;
					camera = new Camera3D({ 0.0f, 0.0f, 10.0f });
					program = &program3DAffine;
				}
			}
			else {
				if (ImGui::Button("2D")) {
					is2D = true;
					delete camera;
					camera = new Camera2D({ 0.0f, 0.0f, 10.0f });
					program = &program2DAffine;
				}
			}

			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void inputMatrix4x4Value(Matrix4x4& matrix) {
	ImGui::BeginTable("Transformation", 4, ImGuiTableFlags_SizingStretchSame);
	for (int row = 0; row < 4; row++)
	{
		ImGui::TableNextRow();
		for (int column = 0; column < 4; column++)
		{
			ImGui::TableSetColumnIndex(column);

			std::string value = matrix[column][row];
			ImGui::SetNextItemWidth(-1.0f);

			if (ImGui::InputText((std::to_string(row) + std::to_string(column)).c_str(), &value) && value.length() > 0) {
				matrix[column][row] = Expression(value);
			}
		}
	}
	ImGui::EndTable();
	matrix.generateFloatData();
}

void inputMatrix3x3Value(Matrix3x3& matrix, std::vector<Vec3>& eigenvectors) {
	ImGui::BeginTable("Transformation", 4, ImGuiTableFlags_SizingStretchSame);
	for (int row = 0; row < 3; row++)
	{
		ImGui::TableNextRow();
		for (int column = 0; column < 3; column++)
		{
			ImGui::TableSetColumnIndex(column);

			std::string value = matrix[column][row];
			ImGui::SetNextItemWidth(-1.0f);

			if (ImGui::InputText((std::to_string(row) + std::to_string(column)).c_str(), &value) && value.length() > 0) {
				matrix[column][row] = Expression(value);
				eigenvectors = matrix.calculateEigenvectors();
			}
		}
	}
	ImGui::EndTable();
	matrix.generateFloatData();
}

void inputMatrix2x2Value(Matrix2x2& matrix, std::vector<Vec2>& eigenvectors) {
	ImGui::BeginTable("Transformation", 4, ImGuiTableFlags_SizingStretchSame);
	for (int row = 0; row < 2; row++)
	{
		ImGui::TableNextRow();
		for (int column = 0; column < 2; column++)
		{
			ImGui::TableSetColumnIndex(column);

			std::string value = matrix[column][row];
			ImGui::SetNextItemWidth(-1.0f);

			if (ImGui::InputText((std::to_string(row) + std::to_string(column)).c_str(), &value) && value.length() > 0) {
				matrix[column][row] = Expression(value);
				matrix.generateFloatData();
				eigenvectors = matrix.calculateEigenvectors();
			}
		}
	}
	ImGui::EndTable();
	
}

GLFWwindow* initialise() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(960, 540, "CAS", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	Input::initialise(window);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
	return window;
}