#version 330 core

//  Group:
//  Brian R., breber@iastate.edu
//  Shrabya K., shrabya@iastate.edu
//  Andrew M., amaxim@iastate.edu
//  Kyle V., vansicek@iastate.edu 

// The vertex buffer input
in vec3 in_Color;
in vec3 in_Position;
in vec3 in_Normal;

// Transformations for the projections
uniform mat4 projectionMatrixBox;
uniform mat4 viewMatrixBox;
uniform mat4 modelMatrixBox;
uniform mat4 inverseViewMatrix;

// The material parameters
uniform vec3 diffuse_color;
uniform vec3 ambient_color;
uniform vec3 specular_color;
uniform float shininess;

struct Light
{
    bool valid;

    // Position of the light source
    vec4 pos;

    // New parameters for the spotlight
    float cone_angle;
    vec3 cone_direction;

    // The intensity values for the reflection equations
    float diffuse_intensity;
    float ambient_intensity;
    float specular_intensity;
    float attenuationCoefficient;
};

uniform Light lights[8];
uniform int numLights;

// The output color
out vec3 pass_Color;

void main(void)
{
	vec3 normal = normalize(in_Normal);
    vec4 transformedNormal = normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));
    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
    vec3 linearColor = vec3(0.0, 0.0, 0.0);

    // Go through the number of lights that the C++ program says there are
    for (int index = 0; index < numLights; index++)
    {
        Light l = lights[index];
        vec4 surface_to_light = normalize(l.pos - surfacePostion);

        // Diffuse color
        float diffuse_coefficient = max(dot(transformedNormal, surface_to_light), 0.0);
        vec3 diffuseColor = diffuse_color * diffuse_coefficient * l.diffuse_intensity;

        // Ambient color
        vec3 ambientColor = vec3(ambient_color) * l.ambient_intensity;

        // Specular color
        vec3 incidenceVector = -surface_to_light.xyz;
        vec3 reflectionVector = reflect(incidenceVector, normal.xyz);
        vec3 cameraPosition = vec3( inverseViewMatrix[3][0], inverseViewMatrix[3][1], inverseViewMatrix[3][2]);
        vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
        float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);
        float specular_coefficient = pow(cosAngle, shininess);
        vec3 lightSpecularColor = specular_color * specular_coefficient * l.specular_intensity;

    	// attenuation
        float distanceToLight = length(l.pos.xyz - surfacePostion.xyz);
        float attenuation = 1.0 / (1.0 + l.attenuationCoefficient * pow(distanceToLight, 2));

        // Spotlight
        if (l.cone_angle != 0.0) {
            // 1. Normalize the cone direction
            vec3 cone_direction_norm = normalize(l.cone_direction);

            // 2. Calculate the ray direction. We already calculated the surface to light direction.
            // 	  All what we need to do is to inverse this value
            vec3 ray_direction = -surface_to_light.xyz;

            // 3. Calculate the angle between light and surface using the dot product again.
            //    To simplify our understanding, we use the degrees
            float light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ;

            // 4. Last, we compare the angle with the current direction and
            //    reduce the attenuation to 0.0 if the light is outside the angle.
        	if (light_to_surface_angle > l.cone_angle) {
          		attenuation = 0.0;
        	}
        }

        linearColor = linearColor +
                      ambientColor +
                      attenuation * (diffuseColor + lightSpecularColor);
    }

	// Gamma correction
	vec3 gamma = vec3(1.0/2.2);
	vec3 finalColor = pow(linearColor, gamma);

	// Pass the color
	pass_Color = finalColor;

	// Passes the projected position to the fragment shader / rasterization process.
    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);
}
