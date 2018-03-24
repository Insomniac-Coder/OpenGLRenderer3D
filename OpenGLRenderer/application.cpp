#include "display.h" 
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char* argv[]) {
	Display display(WIDTH, HEIGHT, "OpenGL Renderer");

	Vertex vertices[] = {Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0,0.0)),
						 Vertex(glm::vec3(   0, 0.5,0), glm::vec2(0.5,1.0)),
						 Vertex(glm::vec3( 0.5,-0.5,0), glm::vec2(1.0,0.5))};

	unsigned int indicies[] = { 0, 1, 2 };


	float z = -4.0f;

	Camera cam(glm::vec3(0.0f, 0.0f, z), 70.f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indicies, sizeof(indicies) / sizeof(indicies[0]), "../res/bricks.jpg", "../res/BasicShader");
	Mesh mesh2("../res/file.obj", "../res/bricks.jpg", "../res/BasicShader");

	//Shader shader("../res/BasicShader");

	//shader.ShaderBind();

	float counter = 0.0f;

	while (!display.WindowClosed()) {
		display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		if (display.CamMovement == 1)
			cam.SetPosition(glm::vec3(0, 0, 0.01));
		else if (display.CamMovement == -1)
			cam.SetPosition(glm::vec3(0, 0, -0.01));
		else if (display.CamMovement == 0)
			cam.SetPosition(glm::vec3(0, 0, 0.0));
		else if (display.CamMovement == 0.5)
			cam.SetPosition(glm::vec3(0.01, 0, 0));
		else if (display.CamMovement == -0.5)
			cam.SetPosition(glm::vec3(-0.01, 0, 0));
		else if (display.CamMovement == 0.1)
			display.movement = !display.movement;

		if (display.movement) {
			mesh2.GetPosition().x = sinf(counter) * 0.3f;
			mesh2.GetPosition().z = cosf(counter) * 0.3f;
			mesh2.GetRotation().z = counter * 0.4f;//cosf(counter);
			mesh2.GetRotation().x = counter * 0.4f;
			mesh2.GetRotation().y = counter * 0.4f;

		}

		mesh2.Draw(cam);
		//mesh.Draw(cam);
		//mesh.SetPosition(glm::vec3(0,0,0));

		display.Update();
		counter += 0.01f;
	}
	return 0;
}