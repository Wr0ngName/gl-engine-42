#version 330 core 
  
#define GLE_OUT_FRAGMENT_COLOR_LOCATION 0 
#define NB_POINT_LIGHTS %nb_point_lights  
  
layout (location = GLE_OUT_FRAGMENT_COLOR_LOCATION) out vec4 gle_FragColor; 

layout(std140) uniform materialBlock
{
	uniform vec4 gle_ambientColor;
	uniform vec4 gle_diffuseColor;
	uniform vec4 gle_specularColor;
	uniform float gle_shininess;
	uniform float gle_specularIntensity;
	uniform float gle_diffuseIntensity;
};

uniform vec3 gle_fogColor;

uniform sampler2D gle_colorMap;
uniform bool gle_hasColorMap;

#if NB_POINT_LIGHTS > 0
	uniform vec3 gle_pointLightColor[NB_POINT_LIGHTS];
	uniform vec3 gle_pointLightSpecularColor[NB_POINT_LIGHTS];
#endif

in float gle_varying_fogFactor; 
in vec3 gle_varying_vLightWeighting;
in float gle_varying_vLightAttenuation;
in vec2 gle_varying_vTextureCoord;
#if NB_POINT_LIGHTS > 0
	in vec3 gle_varying_normal;
	in vec3 gle_varying_eyeDirection;
	in vec3 gle_varying_pointLightDirection[NB_POINT_LIGHTS];
	in float gle_varying_pointLightAttenuation[NB_POINT_LIGHTS];
#endif

void main(void) { 
	vec3 lightWeighting = gle_varying_vLightWeighting;
	vec3 N = normalize(gle_varying_normal);
	vec3 E = normalize(gle_varying_eyeDirection);
	#if NB_POINT_LIGHTS > 0
		for (int i = 0; i < NB_POINT_LIGHTS; ++i)
		{
			vec3 L = normalize(gle_varying_pointLightDirection[i]);
			if (gle_diffuseIntensity > 0)
			{
				float pointLightWeighting = max(dot(N, L), 0.0);
				lightWeighting += gle_pointLightColor[i] * gle_diffuseColor.rgb * pointLightWeighting * gle_diffuseIntensity * 
				gle_varying_pointLightAttenuation[i];
			}
			if (gle_specularIntensity > 0)
			{
				vec3 reflectionDirection = reflect(-L, N);
				float pointLightSpecularWeighting = pow(max(dot(reflectionDirection, E), 0.0), gle_shininess);
				lightWeighting += gle_pointLightSpecularColor[i] * gle_specularColor.rgb
							* pointLightSpecularWeighting * gle_specularIntensity * gle_varying_pointLightAttenuation[i];
			}
		}
	#endif

	vec2 tmp = vec2(gle_varying_vTextureCoord.x, -gle_varying_vTextureCoord.y);
	if (gle_hasColorMap)
	{
		gle_FragColor = texture2D(gle_colorMap, tmp) * vec4(lightWeighting, 1.0);
	}
	else
	{
		gle_FragColor = vec4(lightWeighting, 1.0);
	}
	gle_FragColor = mix(vec4(gle_fogColor, 1.0), gle_FragColor, gle_varying_fogFactor);
}
