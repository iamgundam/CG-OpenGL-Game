#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>


#include <iostream>
#include <string>

#define PI 3.14159265

// Box coordinate with 36 vertices.
// Every 3 coordinates will form 1 triangle.
// The last 2 columns represent texture coordinate for mapping.
float box[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
unsigned int loadTexture(char const * path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
float brightness = 1.0f;
glm::vec3 s_camera_pos = glm::vec3(0.0f, 0.9f,  3.0f);
glm::vec3 s_camera_front = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 s_camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
glm::vec3 s_light_pos(0.0f, 1.0f, 0.1f);
glm::vec3 s_sven_pos(0.0f, 0.4f, 2.0f);
glm::vec3 s_sheep_pos(0.0f, 0.7f, -4.0);
glm::vec3 s_obelisk_pos(0.0f, 2.5f, 8.0f);

// camera
glm::vec3 camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
glm::vec3 camera_front = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
float lastX = 400, lastY = 400;
float pitch = 0;
float yaw = 0;
bool firstMouse = true;
bool USE_ORTHO = false; //Projection type

//jumping
const float INITIAL_JUMP_SPEED = 0.15f;
bool jumping = false;
float jumpSpeed = INITIAL_JUMP_SPEED;

// Interactable positions
glm::vec3 light_pos(0.0f, 1.0f, 0.1f);
glm::vec3 sven_pos(0.0f, 0.4f, 2.0f);
glm::vec3 sheep_pos(0.0f, 0.7f, -4.0);
glm::vec3 obelisk_pos(0.0f, 2.5f, 8.0f);

// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;

// Toggle states
bool BUTTON_PRESSED = false;
int BUTTON_DELAY = 0;
bool BUTTON_CLOSE_ENOUGH = false;

bool SVEN_GRABBED = false;
bool SVEN_CLOSE_ENOUGH = false;

bool ALIVE = true;
bool SET_DEATH_CAMERA = false;

bool VICTORY = false;

int SHOW_DELAY = 0;
bool BRIGHT_TOGGLE = false;

//Animation Variables
float sheep_spin_x = 0.0;
float sven_spin_y = 0.0;
float obelisk_spin_y = 0.0;
float obelisk_translate_y = 0.0;

// Countdown until the button trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_delay()
{
	if(BUTTON_DELAY > 0) BUTTON_DELAY -= 1;
	if(SHOW_DELAY > 0) SHOW_DELAY -= 1;
}

void toggle_button_distance(glm::vec3 light_pos)
{
	if(glm::length(camera_pos - light_pos) <= 1.6f)
		BUTTON_CLOSE_ENOUGH = true;
	else
		BUTTON_CLOSE_ENOUGH = false;
}

void toggle_sven_distance(glm::vec3 sven_pos)
{
	if(glm::length(camera_pos - sven_pos) <= 1.6f)
		SVEN_CLOSE_ENOUGH = true;
	else
		SVEN_CLOSE_ENOUGH = false;
}

void toggle_enemy_hit(glm::vec3 camera_pos)
{
	//If close enough to sheep or obelisk, die
	if(glm::length(camera_pos - sheep_pos) <= 1.6f ||
	   glm::length(camera_pos - obelisk_pos) <= 2.0f )
		ALIVE = false;
}

void toggle_game_won()
{
	if(glm::length(camera_pos - glm::vec3(-8.0f, 0.5f, -4.0f))<= 1.0f && SVEN_GRABBED == true)
		VICTORY = true;
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement for OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "uh oh water sheep", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lighting_shader("./sample2.vs", "./sample2.fs");
	Shader lamp_shader("./lamp.vs", "./lamp.fs");

    // capture mouse input and hide the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO_box, VAO_box;

	glGenVertexArrays(1, &VAO_box);
	glGenBuffers(1, &VBO_box);

	glBindVertexArray(VAO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

	//vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int VAO_light;
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);





	// load and create a texture 
	// -------------------------
	unsigned int tex_wood_diffuse, tex_street_diffuse, tex_grass_diffuse, tex_marble_diffuse, tex_curtin_diffuse;
	unsigned int tex_wood_specular, tex_street_specular, tex_grass_specular, tex_marble_specular, tex_curtin_specular;

	unsigned int tex_dog_diffuse, tex_dog2_diffuse, tex_restart_diffuse, tex_obelisk_diffuse, tex_container_diffuse;
	unsigned int tex_dog_specular, tex_dog2_specular, tex_restart_specular, tex_obelisk_specular, tex_container_specular;

	tex_wood_diffuse = loadTexture(FileSystem::getPath("resources/textures/wood2.jpg").c_str());
	tex_wood_specular = loadTexture(FileSystem::getPath("resources/textures/wood2_specular.jpg").c_str());
	tex_street_diffuse = loadTexture(FileSystem::getPath("resources/textures/street.png").c_str());
	tex_street_specular = loadTexture(FileSystem::getPath("resources/textures/street_specular.png").c_str());
	tex_grass_diffuse = loadTexture(FileSystem::getPath("resources/textures/grass.jpg").c_str());
	tex_grass_specular = loadTexture(FileSystem::getPath("resources/textures/grass_specular.jpg").c_str());
	tex_marble_diffuse = loadTexture(FileSystem::getPath("resources/textures/marble.jpg").c_str());
	tex_marble_specular = loadTexture(FileSystem::getPath("resources/textures/marble_specular.jpg").c_str());

	tex_dog_diffuse = loadTexture(FileSystem::getPath("resources/textures/dog.jpg").c_str());
	tex_dog_specular = loadTexture(FileSystem::getPath("resources/textures/dog_specular.jpg").c_str());
	tex_dog2_diffuse = loadTexture(FileSystem::getPath("resources/textures/dog2.jpg").c_str());
	tex_dog2_specular = loadTexture(FileSystem::getPath("resources/textures/dog2_specular.jpg").c_str());
	tex_restart_diffuse = loadTexture(FileSystem::getPath("resources/textures/restart.jpg").c_str());
	tex_restart_specular = loadTexture(FileSystem::getPath("resources/textures/restart_specular.jpg").c_str());
	tex_obelisk_diffuse = loadTexture(FileSystem::getPath("resources/textures/obelisk.jpg").c_str());
	tex_obelisk_specular = loadTexture(FileSystem::getPath("resources/textures/obelisk_specular.jpg").c_str());
	tex_container_diffuse = loadTexture(FileSystem::getPath("resources/textures/container2.png").c_str());
	tex_container_specular = loadTexture(FileSystem::getPath("resources/textures/container2_specular.png").c_str());

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

	    lighting_shader.use();
	    lighting_shader.setInt("material.diffuse", 0);
	    lighting_shader.setInt("material.specular", 1);

        //Display as either perspective or orthographic based on user toggle
        glm::mat4 projection;
        if(USE_ORTHO)
        {
            projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -100.0f, 100.0f);
        }
        else
        {
            projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
	    }
        lighting_shader.setMat4("projection", projection);

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		//update delay countdown
		update_delay();

		// input
		// -----
		process_input(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


		// activate shader
		lighting_shader.use();
		lighting_shader.setVec3("light.position", light_pos);
        lighting_shader.setVec3("viewPos", camera_pos);

		// light properties
        if(BRIGHT_TOGGLE)
        {
		    lighting_shader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
        }
        else
        {
		    lighting_shader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
        }

		if(BUTTON_PRESSED == true)
		{
			lighting_shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
			lighting_shader.setVec3("light.specular", 0.5f, 0.5f, 0.5f);
		}
		else
		{
			lighting_shader.setVec3("light.diffuse", 0.0f, 0.0f, 0.0f);
			lighting_shader.setVec3("light.specular", 0.0f, 0.0f, 0.0f);
		}

		// material properties
        	lighting_shader.setFloat("material.shininess", 65.0f);
			lighting_shader.setFloat("light.strength", brightness);
		// for now just set the same for every object. But, you can make it dynamic for various objects.


		// camera/view transformation
		glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
		
		//If dead, move to floor
		if(!ALIVE)
		{
			//Only set the camera up once after dying
			if(!SET_DEATH_CAMERA)
			{
				camera_up = cross(camera_front, camera_up);
				SET_DEATH_CAMERA = true;
			}
			camera_pos[1] = 0.1f;
		}

		lighting_shader.setMat4("view", view);

		//declare transformation matrix
		glm::mat4 model = glm::mat4();


		//Draw objects
		//----------------------------------------------------------------------------------

		// Restart text
		if(!ALIVE)
		{
			glBindVertexArray(VAO_box);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_restart_diffuse);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_restart_specular);

			model = glm::mat4();
			model = glm::translate(model, (camera_pos + camera_front));
			model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.0f));

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//Street
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_street_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_street_specular);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(9.0f, 0.001f, 700.0f));

		lighting_shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Grass
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f));
		model = glm::scale(model, glm::vec3(700.0f, 0.001f, 700.0f));

		lighting_shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

        //Water sheep
        glm::vec3 sheep_scales[] = {
            glm::vec3(0.5f, 0.5f, 1.0f), //Body
            glm::vec3(0.25f, 0.25f, 0.25f), //Head
            glm::vec3(0.2f, 0.5f, 0.2f), //Front left leg
            glm::vec3(0.2f, 0.5f, 0.2f), //Front right leg
            glm::vec3(0.2f, 0.5f, 0.2f), //Back left leg
            glm::vec3(0.2f, 0.5f, 0.2f), //Back right leg
        };
        glm::vec3 sheep_positions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f), //Body
            glm::vec3(0.0f, 0.25f, 0.5f), //Head
            glm::vec3(0.15f, -0.5f, 0.35f), //Front left leg
            glm::vec3(-0.15f, -0.5f, 0.35f), //Front right leg
            glm::vec3(0.15f, -0.5f, -0.35f), //Back left leg
            glm::vec3(-0.15f, -0.5f, -0.35f), //Back right leg
        };

		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_dog2_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_dog_specular);

		for(int tab = 0; tab < 6; tab++)
		{	
			float sheepSpeed = 0.5f;
			model = glm::mat4();

			if(VICTORY)
			{
				//Fly up to sky
				sheep_pos[1] += 1.0f*delta_time;
				model = glm::translate(model, sheep_pos);
			}
			//Follow player when player grabs Sven
			else if(SVEN_GRABBED)
			{
				if(ALIVE)//Stop when player dies
				{
					sheep_pos += sheepSpeed * delta_time * glm::normalize(camera_pos - sheep_pos);
					sheep_pos[1] = 0.7f; //Lock height
				}

				//Spinspeed
				sheep_spin_x += 4.0f;
				if(abs(sheep_spin_x - 360.0f) <= 0.1f) sheep_spin_x = 0.0f;

				model = glm::translate(model, sheep_pos);
				model = glm::rotate(model, glm::radians(yaw + 90.0f), glm::vec3(0.0f, -1.0f, 0.0f)); //Face the camera
				model = glm::rotate(model, glm::radians(sheep_spin_x), glm::vec3(1.0f, 0.0f, 0.0f)); //Animation
			}
			else //Stop
			{
				model = glm::translate(model, sheep_pos);
				model = glm::rotate(model, glm::radians(yaw + 90.0f), glm::vec3(0.0f, -1.0f, 0.0f)); //Face the camera
			}	

			model = glm::translate(model, sheep_positions[tab]);
			model = glm::scale(model, sheep_scales[tab]);

			toggle_enemy_hit(camera_pos);
			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

        //Sven
        glm::vec3 sven_scales[] = {
            glm::vec3(0.3f, 0.3f, 0.5f), //Body
            glm::vec3(0.2f, 0.2f, 0.2f), //Head
            glm::vec3(0.1f, 0.1f, 0.12f), //Muzzle
            glm::vec3(0.05f, 0.15f, 0.04),  //Left ear
            glm::vec3(0.05f, 0.15f, 0.04),  //Right ear
			glm::vec3(0.08f, 0.2f, 0.08f),    //Front left leg
			glm::vec3(0.08f, 0.2f, 0.08f),    //Front right leg
			glm::vec3(0.08f, 0.2f, 0.08f),    //Back left leg
			glm::vec3(0.08f, 0.2f, 0.08f),    //Back right leg
			glm::vec3(0.05f, 0.05f, 0.3f),    //Tail

        };
        glm::vec3 sven_positions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f), //Body
            glm::vec3(0.0f, 0.0f, 0.3f), //Head
            glm::vec3(0.0f, -0.05f, 0.42f), //Muzzle
            glm::vec3(0.08f, 0.15f, 0.35f),  //Left ear
            glm::vec3(-0.08f, 0.15f, 0.35f), //Right ear
			glm::vec3(0.08f, -0.25f, 0.2f), //Front left leg
			glm::vec3(-0.08f, -0.25f, 0.2f), //Front right leg
			glm::vec3(0.08f, -0.25f, -0.2f), //Back left leg
			glm::vec3(-0.08f, -0.25f, -0.2f), //Back right leg
			glm::vec3(0.0f, 0.10, -0.4)
        };

		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_dog_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_dog_specular);

		for(int tab = 0; tab < 10; tab++)
		{	
			model = glm::mat4();
			

			if(SVEN_GRABBED)
			{
				//Set position to left of camera
				sven_pos = camera_pos + camera_front - 0.4f*cross(camera_front,camera_up);
				model = glm::translate(model, sven_pos);
				model = glm::rotate(model, glm::radians(yaw - 90.0f), glm::vec3(0.0f, -1.0f, 0.0f)); //Face camera on x
			}
			else
			{
				sven_spin_y += 0.5f;
				if(abs(sven_spin_y - 360.0f) <= 0.1f) sven_spin_y = 0.0f;

				//Standing on ground
				model = glm::translate(model, glm::vec3(sven_pos[0], 0.4f, sven_pos[2]));
				model = glm::rotate(model, glm::radians(sven_spin_y), glm::vec3(0.0f, 1.0f, 0.0f)); //Animation

			}

			model = glm::translate(model, sven_positions[tab]);
			model = glm::scale(model, sven_scales[tab]);

			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		toggle_sven_distance(sven_pos);

        //Trees
        glm::vec3 tree_scales[] = {
            glm::vec3(0.5f, 3.0f, 0.5f), //trunk
            glm::vec3(3.0f, 1.0f, 3.0f),  //leaves bottom
            glm::vec3(2.0f, 1.0f, 2.0f),  //leaves mid
            glm::vec3(1.0f, 1.0f, 1.0f),  //leaves top
        };
        glm::vec3 tree_positions[] = {
            glm::vec3(0.0f, 1.5f, 0.0f),  //trunk
            glm::vec3(0.0f, 3.5f, 0.0f), //leaves bottom
            glm::vec3(0.0f, 4.5f, 0.0f), //leaves mid
            glm::vec3(0.0f, 5.5f, 0.0f), //leaves top
        };

        //Multiple trees in world, array to store their positions
        glm::vec3 tree_copy_positions[] = {     
            glm::vec3(-5.0f, 0.0f, 0.0f), //Middle left
            glm::vec3(5.0f, 0.0f, 0.0f),  //Middle right
            glm::vec3(-5.0f, 0.0f, 6.0f), //Forward left
            glm::vec3(5.0f, 0.0f, 6.0f),  //Forward right
            glm::vec3(-5.0f, 0.0f, -6.0f), //Back left
            glm::vec3(5.0f, 0.0f, -6.0f),  //Back right
        };

        //Iterate through tree copies
        for(int ii=0; ii<6; ii++)
        { 
            //Leaves
            glBindVertexArray(VAO_box);

	    	glActiveTexture(GL_TEXTURE0);
	    	glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
    		glActiveTexture(GL_TEXTURE1);
    		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

    		for(int tab = 1; tab < 4; tab++)
	    	{	
                model = glm::mat4();
                model = glm::translate(model, tree_positions[tab]);
                model = glm::translate(model, tree_copy_positions[ii]);
                model = glm::scale(model, tree_scales[tab]);

                lighting_shader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            //Trunk
            glBindVertexArray(VAO_box);

		    glActiveTexture(GL_TEXTURE0);
		    glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
		    glActiveTexture(GL_TEXTURE1);
    		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
   
            model = glm::mat4();
            model = glm::translate(model, tree_positions[0]);
            model = glm::translate(model, tree_copy_positions[ii]);
            model = glm::scale(model, tree_scales[0]);

            lighting_shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

		//SPECIAL TREE
        glm::vec3 special_tree_scales[] = {
            glm::vec3(1.0f, 2.0f, 1.0f), //trunk
            glm::vec3(3.0f, 1.0f, 3.0f),  //leaves bottom
            glm::vec3(2.0f, 1.0f, 2.0f),  //leaves mid
            glm::vec3(1.0f, 2.0f, 1.0f),  //leaves top
        };
        glm::vec3 special_tree_positions[] = {
            glm::vec3(0.0f, 1.0f, 0.0f),  //trunk
            glm::vec3(0.0f, 2.5f, 0.0f), //leaves bottom
            glm::vec3(0.0f, 3.5f, 0.0f), //leaves mid
            glm::vec3(0.0f, 5.0f, 0.0f), //leaves top
        };
        //Multiple trees in world, array to store their positions
        glm::vec3 special_tree_copy_positions[] = {     
            glm::vec3(-10.0f, 0.0f, 0.0f), //Middle left
            glm::vec3(10.0f, 0.0f, 0.0f),  //Middle right
            glm::vec3(-10.0f, 0.0f, 8.0f), //Forward left
            glm::vec3(10.0f, 0.0f, 8.0f),  //Forward right
            glm::vec3(-10.0f, 0.0f, -8.0f), //Back left
            glm::vec3(10.0f, 0.0f, -8.0f),  //Back right
			glm::vec3(-10.0f, 0.0f, -10.0f), //Far back left
			glm::vec3(10.0f, 0.0f, -10.0f),   //Far back right
			glm::vec3(-10.0f, 0.0f, 10.0f),	//Far forward left
			glm::vec3(10.0f, 0.0f, 10.0f),   //Far forward right
        };

        //Iterate through tree copies
        for(int ii=0; ii<10; ii++)
        { 
            //Leaves
            glBindVertexArray(VAO_box);

	    	glActiveTexture(GL_TEXTURE0);
	    	glBindTexture(GL_TEXTURE_2D, tex_grass_diffuse);
    		glActiveTexture(GL_TEXTURE1);
    		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

    		for(int tab = 1; tab < 4; tab++)
	    	{	
                model = glm::mat4();
                model = glm::translate(model, special_tree_positions[tab]);
                model = glm::translate(model, special_tree_copy_positions[ii]);
                model = glm::scale(model, special_tree_scales[tab]);

                lighting_shader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            //Trunk
            glBindVertexArray(VAO_box);

		    glActiveTexture(GL_TEXTURE0);
		    glBindTexture(GL_TEXTURE_2D, tex_wood_diffuse);
		    glActiveTexture(GL_TEXTURE1);
    		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
   
            model = glm::mat4();
            model = glm::translate(model, special_tree_positions[0]);
            model = glm::translate(model, special_tree_copy_positions[ii]);
            model = glm::scale(model, special_tree_scales[0]);

            lighting_shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


		// Obelisk of marks
		glm::vec3 obelisk_positions[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),  //Main pillar
			glm::vec3(0.0f, 2.5f, 0.0f),  //Top step
			glm::vec3(3.0f, 0.0f, 0.0f),  //Orbiting box
		};
		glm::vec3 obelisk_scales[] = {
			glm::vec3(2.0f, 5.0f, 2.0f),  //Main pillar
			glm::vec3(1.0f, 3.0f, 1.0f),  //Top step
			glm::vec3(1.0f, 1.0f, 1.0f),  //Orbiting box
		};
	
        glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
	   	glBindTexture(GL_TEXTURE_2D, tex_obelisk_diffuse);
    	glActiveTexture(GL_TEXTURE1);
    	glBindTexture(GL_TEXTURE_2D, tex_obelisk_specular);

    	for(int tab = 0; tab < 3; tab++)
	   	{	
            model = glm::mat4();			
			float obeliskSpeed = 0.3f;

			if(VICTORY)
			{
				//Fly up to sky
				obelisk_pos[1] += 1.0f*delta_time;
			}
			//Follow player when player grabs Sven
			else if(SVEN_GRABBED)
			{					
				obelisk_pos += obeliskSpeed * delta_time * glm::normalize(camera_pos - obelisk_pos);
				obelisk_pos[1] = 2.5f;

				if(ALIVE)//Stop when player dies
				{
					obelisk_pos += obeliskSpeed * delta_time * glm::normalize(camera_pos - obelisk_pos);
					obelisk_pos[1] = 2.5f; //Lock height
				}

				//Spinspeed
				obelisk_spin_y += 4.0f;
				if(abs(obelisk_spin_y - 360.0f) <= 0.1f) obelisk_spin_y = 0.0f;
			}

			model = glm::translate(model, obelisk_pos);

			//Rotate orbiting box only
			if(tab == 2)
			{
				obelisk_spin_y += 0.5f;
				if(abs(obelisk_spin_y - 360.0f) <= 0.1f) obelisk_spin_y = 0.0f;
				model = glm::rotate(model, glm::radians(obelisk_spin_y), glm::vec3(0.0f, 1.0f, 0.0f));
			}
            model = glm::translate(model, obelisk_positions[tab]);
            model = glm::scale(model, obelisk_scales[tab]);
            lighting_shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

		//Winner door
		glm::vec3 winner_door_positions[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),  //Door
			glm::vec3(0.2f, 0.0f, 0.0f)   //Knob
		};
		glm::vec3 winner_door_scales[] = {
			glm::vec3(0.5f, 1.0f, 0.1f),  //Door
			glm::vec3(0.1f, 0.1f, 0.2f)	 //Knob
		};

        glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
	   	glBindTexture(GL_TEXTURE_2D, tex_container_diffuse);
    	glActiveTexture(GL_TEXTURE1);
    	glBindTexture(GL_TEXTURE_2D, tex_container_specular);

		for(int tab=0; tab<2; tab++)
		{
			model = glm::mat4();

			model = glm::translate(model, glm::vec3(-8.0f, 0.5f, -4.0f));
        	model = glm::translate(model, winner_door_positions[tab]);
        	model = glm::scale(model, winner_door_scales[tab]);
        	lighting_shader.setMat4("model", model);
        	glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		toggle_game_won();


		// Light cube
		lamp_shader.use();
		lamp_shader.setMat4("projection", projection);
		lamp_shader.setMat4("view", view);
		
		model = glm::mat4();
		model = glm::translate(model, light_pos);

        //Check and update distance to light
        toggle_button_distance(light_pos);

		if(BUTTON_PRESSED == true) 
        {
			//Position = translate to camera, forward to front vector, cross vector to side
			light_pos = camera_front + camera_pos + 0.3f*cross(camera_front, camera_up);

            lamp_shader.setFloat("intensity", 1.0);
            model = glm::mat4();
			model = glm::translate(model, light_pos);
			model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, -1.0f, 0.0f)); //Face camera on x
        }
		else
        {
            lamp_shader.setFloat("intensity", 0.3);
            light_pos[1] = 0.1f;
        }

		model = glm::scale(model, glm::vec3(0.02f, 0.10f, 0.02f));
		lamp_shader.setMat4("model", model);
		glBindVertexArray(VAO_light);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_box);
	glDeleteBuffers(1, &VBO_box);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
    float cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
       	glfwSetWindowShouldClose(window, true);

	//Allow movement only if not dead
	if(ALIVE)
	{
		// double speed with "Shift" pressed
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
			cameraSpeed = 2.5 * delta_time; 
		else
			cameraSpeed = 2.5 * delta_time * 2;	

		// Movement on WASD
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera_pos += cameraSpeed * camera_front;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera_pos -= cameraSpeed * camera_front;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
		}

		//Jumping
		if(!jumping)
		{
			//Restrict camera height when not jumping
			camera_pos[1] = 0.9f;
		}
		else
		{
			//Decrease acceleration by an increment;
			if(camera_pos[1] > 0.9f)
			{
				jumpSpeed = jumpSpeed - 0.01f;
			}

			//Move camera by positive or negative y
			camera_pos[1] += jumpSpeed;

			//Reached ground, stop jumping and reset jump speed
			if(camera_pos[1] < 0.9f)
			{
				jumping = false;
				jumpSpeed = INITIAL_JUMP_SPEED;

				//Set to normal y pos
				camera_pos[1] = 0.9f;
			}
		}
		// Begin jump when SPACE is pressed ONLY when on ground
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if(jumping == false)
				jumping = true;
		}

		//pick up light
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && BUTTON_DELAY == 0 && BUTTON_CLOSE_ENOUGH == true)
		{
			//Cannot pick up or drop when jumping
			if(!jumping)
			{
				BUTTON_DELAY = 20;
				if(BUTTON_PRESSED == false) 		
					BUTTON_PRESSED = true;
				else
					BUTTON_PRESSED = false;
			}
		}

		//pick up Sven
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && BUTTON_DELAY == 0 && SVEN_CLOSE_ENOUGH == true)
		{
			//Cannot pick up or drop when jumping
			if(!jumping)
			{
				BUTTON_DELAY = 20;
				if(SVEN_GRABBED == false) 		
					SVEN_GRABBED = true;
				else
					SVEN_GRABBED = false;
			}
		}

		// make light brighter
		if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && SHOW_DELAY == 0)
		{
			BUTTON_DELAY = 20;
			brightness += 0.07f;
			if(brightness > 10.0f) brightness = 10.0f; //Limit brightness to 10x brighter than default 1.0
		}

		// make light darker
		if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && SHOW_DELAY == 0)
		{
			BUTTON_DELAY = 20;
			brightness -= 0.07f;
			if(brightness < 0.0f) brightness = 0.0f; //Limit brightness to 0

		}

		//toggle bright scene display
		if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && SHOW_DELAY == 0)
		{
				SHOW_DELAY = 20;
				if(BRIGHT_TOGGLE == false) 		
					BRIGHT_TOGGLE = true;
				else
					BRIGHT_TOGGLE = false;
		}

		//toggle orthographic/perspective display
		if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && SHOW_DELAY == 0)
		{
			SHOW_DELAY = 20;
			if(USE_ORTHO)
			{
				USE_ORTHO = false;
			}
			else
			{
				USE_ORTHO = true;
			}
		}
	}

	//Restart game by resetting interactables and camera to beginning states
	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && BUTTON_DELAY == 0)
	{
		BUTTON_DELAY = 20;
		
		camera_pos = s_camera_pos;
		camera_up = s_camera_up;
		camera_front = s_camera_front;
		light_pos = s_light_pos;
		sheep_pos = s_sheep_pos;
		sven_pos = s_sven_pos;
		obelisk_pos = s_obelisk_pos;

		BUTTON_PRESSED = false;
		SVEN_GRABBED = false;
		ALIVE = true;
		VICTORY = false;
		SET_DEATH_CAMERA = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//Allow mouse control when player is alive
    if(ALIVE)
	{
    	if(firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.03f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;   
		
		if(pitch > 89.0f)
			pitch = 89.0f;
		if(pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front[0] = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front[1] = sin(glm::radians(pitch));
		front[2] = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

		camera_front = glm::normalize(front);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
