#ifndef LIGHT_H
#define LIGHT_H

#define GLEW_STATIC5
#include "glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
	We will be using "Phong Lighting Model" as lighting model.

	This major blocks of this model are:
	+ ambient,
	+ diffuse,
	+ specular,
	-----------------
	combined -> Phong Lighting Model.

	Ambient lighting: Is always so objects are almost never completly dark, for example moon can gives that light.
					  Usually does not come for a single source, but from many light sources scattered all around us, even when they're not immediately visible.
					  The main proporties of light is that it can scatter and bounce in many directions. 
				      Light can thus reflect on other surfaces and have an indirect import on the light of an object.

	
	Diffuse lighting: Ambient lighting doesn't gives us the most interesting results, however diffuse lighting will start to give significant visual impact on the object.
					  This lighting gives the object more brightness the closer its fragments are aligned to the light rays from light source.
					  So we need to measure at what angle the light ray touches the fragment. If the light rays is perpendicular to the object's surface the light has the greatest impact.
					  To measure the angle between light ray and fragment we will use normal vector, that is vector perpendicular to the fragment's surface.
					  We will calculate angle by using dot product. When the angle between both vectors is 90 [deg], the dot product becomes 0.
					  The same applies to theta: the larger theta becomes, the less of an impact of the light will be on the fragment's color.
					  We have to use unit's vector as vector to these calculations.
					  The main vectors:
					  - Normal vector: Vector which is perpendicular to the vertex's surface.
					  - The directed light ray: A direction vector that is the difference vector between the light's position and the fragment's position.
											    To calculate this light ray we need the light's position vector and the fragment's position vector.
							   /\	   /\
							  /  \    /  \
								\      |
								 \     |
								  \  O |
								   \   |
									\  |
									 \ |
									  \|
						--------------------------------
	
	Specular lighting:	Is based on the light's direction vector and the object's normal vectors, but this
						time it's also based on the view direction e.g. from what direction the camera/ player is looking at the fragment.
						Specular lighting is based on the reflective proporties of surfaces. If you think of the object's surface as mirror,
						the specular lighting is the strongest wherever we would see the light reflected on the surface.
						We can calculate "reflection vector" by reflecting the "light direction" around the "normal vector".
						After this we calculate the angular distance between this reflection vector and the view direction.
						The closer the angle between them, the greater impact of the specular light.
						The resulting effect is that we can see a bit of a hightlight when we are looking at light's direction reflected via the surface.
						The "view vector" is the one extra variable we need for specular lighting which we can calculate using the viewer's (camera's) world space position and the fragment's position.
						Then we will calculate the specular's intensity, multiply this with the light color and add this to the ambient and diffuste components.

					(Light) ****	  /\
							****	 /  \
								\      |	  /   Eye or Camera
								 \    N|    R/   /
								  \    |    /   /
								   \   |   / o /
									\  |  /   /
									 \ | /   /
									  \|/   /
						--------------------------------

	Shader program representatio of light:

	struct Light
	{
		vec3 colour;
		float ambientIntensity;
		float diffuseIntensity;
	};

*/

class Light
{
protected:
	glm::vec3 colour;			// Color of rays from lighting.
	GLfloat ambientIntensity;	// Intensity of ambient factor.
	GLfloat diffuseIntensity;	// Intensity of diffuse factor.

public:

	// Getting current colour of light.
	glm::vec3 getColour();

	// Getting value of ambient intensity.
	GLfloat getAmbientIntensity();

	// Getting value of diffuse intensity.
	GLfloat getDiffuseIntensity();

	// Getting reference to the current colour of light.
	glm::vec3& getRefColour()
	{
		return colour;
	}

	// Getting reference to the ambient intensity.
	GLfloat& getRefAmbientIntensity()
	{
		return ambientIntensity;
	}

	// Getting reference to the diffuse intensity.
	GLfloat& getRefDiffuseIntensity()
	{
		return diffuseIntensity;
	}

	// Setting colour by using vector.
	void setColour(glm::vec3 colour);

	// Setting colour by using float as input.
	void setColour(GLfloat red, GLfloat green, GLfloat blue);

	// Setting up the ambient intensity.
	void setAmbientIntensity(GLfloat ambientIntensity);

	// Setting up the diffuse intensity.
	void setDiffuseIntenisty(GLfloat diffuseIntensity);

	// Default constructor.
	Light();

	// Constuctor that takes color and intesities.
	Light(GLfloat red, GLfloat green, GLfloat blue,
		  GLfloat ambientIntensity, GLfloat diffuseIntensity);

	// Customized constructor that takes vectors as input.
	Light(glm::vec3 colour, GLfloat ambientIntensity, GLfloat diffuseIntensity);
};
#endif