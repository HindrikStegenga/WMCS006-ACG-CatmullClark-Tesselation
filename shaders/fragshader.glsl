#version 410
// Fragment shader

layout (location = 0) in vec3 vertcoords_camera_fs;
layout (location = 1) in vec3 vertnormal_camera_fs;

uniform vec3 materialColour;
uniform bool approxFlatShading;

out vec4 fColor;

void main() {

  fColor = vec4(1);
  return;
  vec3 lightpos = vec3(3.0, 0.0, 2.0);
  vec3 lightcolour = vec3(1.0);

  vec3 matcolour = materialColour;
  vec3 matspeccolour = vec3(1.0);

  float matambientcoeff = 0.2;
  float matdiffusecoeff = 0.6;
  float matspecularcoeff = 0.4;

  vec3 normal;
  normal = normalize(vertnormal_camera_fs);

  // A small trick to approximate some form of flat shading.
  // It somewhat approximates the flat surface normal but only on the current triangle.
  // Helps for visibility
  if (approxFlatShading) {
      vec3 xTangent = dFdx(vertcoords_camera_fs);
      vec3 yTangent = dFdy(vertcoords_camera_fs);
      normal = normalize(cross(xTangent, yTangent));
  }
  
  vec3 surftolight = normalize(lightpos - vertcoords_camera_fs);
  float diffusecoeff = max(0.0, dot(surftolight, normal));
  
  vec3 camerapos = vec3(0.0);
  vec3 surftocamera = normalize(camerapos - vertcoords_camera_fs);
  vec3 reflected = 2 * diffusecoeff * normal - surftolight;
  float specularcoeff = max(0.0, dot(reflected, surftocamera));

  vec3 compcolour = min(1.0, matambientcoeff + matdiffusecoeff * diffusecoeff) * lightcolour * matcolour;
       compcolour += matspecularcoeff * specularcoeff * lightcolour * matspeccolour;

  fColor = vec4(compcolour, 1.0);

}
