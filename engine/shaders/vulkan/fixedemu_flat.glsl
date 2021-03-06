!!samps 1

layout(constant_id = 0) const int alphatest = 4;

//this shader is present for support for gles/gl3core contexts
//it is single-texture-with-vertex-colours, and doesn't do anything special.
//beware that a few things use this, including apparently fonts and bloom rescaling.
//its really not meant to do anything special.

#include "sys/defs.h"

layout(location=0) varying vec2 tc;

#ifdef VERTEX_SHADER
void main ()
{
	tc = v_texcoord;
	gl_Position = ftetransform();
}
#endif

#ifdef FRAGMENT_SHADER
layout(push_constant) uniform pushintf
{
	vec4 colour;	
} push;

void main ()
{
	vec4 fc = texture2D(s_t0, tc) * push.colour;
	if (alphatest == 4)
		discard;
	if (alphatest == 3)
	{
		if (fc.a < 0.5)
			discard;
	}
	else if (alphatest == 2)
	{
		if (fc.a <= 0)
			discard;
	}
	else if (alphatest == 1)
	{
		if (fc.a >= 0.5)
			discard;
	}
	gl_FragColor = fc;
}
#endif
