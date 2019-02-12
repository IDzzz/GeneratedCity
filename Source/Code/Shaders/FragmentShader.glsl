#version 330
 
// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform float angle;

uniform vec3 light_positionB;
uniform float angleB;
uniform float building;


// Uniform texture
uniform sampler2D texture;

in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 colorx = texture2D(texture, texcoord);
	vec3 object_color = vec3(colorx.r, colorx.g, colorx.b);
	//out_color = texture2D(texture, texcoord);
	//out_color = vec4(object_color, 1.0);

	vec3 L = normalize(light_position -  world_position);
	vec3 V = normalize(eye_position -  world_position);
	vec3 H = normalize(L + V);
	
	// TODO: define ambient light component
	float ambient_light = 0.45 * material_kd;
	vec3 ambient_light2 = object_color * ambient_light;

	// TODO: compute diffuse light component
	float diffuse_light;
	diffuse_light = material_kd * max(dot(world_normal, L), 0);
	vec3 diffuse_light2 = object_color  * diffuse_light;

	float specular_light;
	int primesteLumina = 0;
	if (diffuse_light > 0)
	{
		primesteLumina = 1;
	}

	// TODO: compute specular light component
	specular_light = material_ks * primesteLumina * pow(max(dot(world_normal, H), 0), 20);
	vec3 specular_light2 = object_color * specular_light;


	// TODO: compute light
	vec3 light;

	float factorAtenuare = 80 / pow(distance(light_position , world_position), 2);
	float cut_off = radians(angle);
	float spot_light = dot(-L, light_direction);
	float spot_light_limit = cos(cut_off);
	float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
	float light_att_factor = pow(linear_att, 2);

	light = ambient_light2 + (factorAtenuare+light_att_factor) * (diffuse_light2 + specular_light2);

	if (building == 1) {
		vec3 L = normalize(light_positionB -  world_position);
		vec3 V = normalize(eye_position -  world_position);
		vec3 H = normalize(L + V);
	
		// TODO: define ambient light component
		float ambient_light = 0.45 * material_kd;
		vec3 ambient_light2 = object_color * ambient_light;

		// TODO: compute diffuse light component
		float diffuse_light;
		diffuse_light = material_kd * max(dot(world_normal, L), 0);
		vec3 diffuse_light2 = object_color  * diffuse_light;

		float specular_light;
		int primesteLumina = 0;
		if (diffuse_light > 0)
		{
			primesteLumina = 1;
		}

		// TODO: compute specular light component
		specular_light = material_ks * primesteLumina * pow(max(dot(world_normal, H), 0), 20);
		vec3 specular_light2 = object_color * specular_light;

		float factorAtenuareB = 1 / pow(distance(light_positionB , world_position), 2);
		float cut_offB = radians(angleB);
		float spot_lightB = dot(-L, light_direction);
		float spot_light_limitB = cos(cut_offB);
		float linear_attB = (spot_lightB - spot_light_limitB) / (1 - spot_light_limitB);
		float light_att_factorB = pow(linear_attB, 2);
		//light = ambient_light2 + (factorAtenuare+light_att_factor+light_att_factorB) * (diffuse_light2 + specular_light2);
		light += (factorAtenuareB + light_att_factorB) * (diffuse_light2 + specular_light2);
	}


	// TODO: write pixel out color
	out_color = vec4(light,colorx.a);
}
