#version 460 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in float vGridSize;
layout(location = 2) in vec3 vViewWorldPos;

layout(location = 0) out vec4 FragColor;

uniform float uGridMinPixelBetweenCells;
uniform float uGridCellSize;
uniform vec4 uGridColorThin;
uniform vec4 uGridColorThick;
uniform float uGridLodBias;

vec2 satv(vec2 v){
    return clamp(v, vec2(0.0), vec2(1.0));
}

float satf(float x){
    float f = clamp(x, 0.0, 1.0);
    return f;
}

float log10(float x){
    float f = log(x) / log(10.0);
    return f;
}

float max2(vec2 v){
    return max(v.x, v.y);
}

void main(){
    vec2 dvx = vec2(dFdx(vWorldPos.x), dFdy(vWorldPos.x));
    vec2 dvy = vec2(dFdx(vWorldPos.z), dFdy(vWorldPos.z));

    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx, ly);

    float l = length(dudv);

    float LOD = max(0.0, log10(l * uGridMinPixelBetweenCells / uGridCellSize) + uGridLodBias);

    float GridCellSizeLod0 = uGridCellSize * pow(10.0, floor(LOD));
    float GridCellSizeLod1 = GridCellSizeLod0 * 10.0;
    float GridCellSizeLod2 = GridCellSizeLod1 * 10.0;

    dudv *= 4.0;

    vec2 mod_div_dudv = mod(vWorldPos.xz, GridCellSizeLod0) / dudv;
    float Lod0a = max2(vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    mod_div_dudv = mod(vWorldPos.xz, GridCellSizeLod1) / dudv;
    float Lod1a = max2(vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    mod_div_dudv = mod(vWorldPos.xz, GridCellSizeLod2) / dudv;
    float Lod2a = max2(vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)));

    float LOD_fade = fract(LOD);

    vec4 Color;

    if (Lod2a > 0.0){
        Color = uGridColorThick;
        Color.a *= Lod2a;
    } else {
        if (Lod1a > 0.0){
            Color = mix(uGridColorThick, uGridColorThin, LOD_fade);
            Color.a *= Lod1a;
        } else {
            Color = uGridColorThin;
            Color.a *= (Lod0a * (1.0 - LOD_fade));
        }
    }

    float xAxis = 1.0 - smoothstep(0.0, fwidth(vWorldPos.z) * 1.5, abs(vWorldPos.z));
    float zAxis = 1.0 - smoothstep(0.0, fwidth(vWorldPos.x) * 1.5, abs(vWorldPos.x));

    vec4 xColor = vec4(1.0, 0.0, 0.0, xAxis); // red
    vec4 zColor = vec4(0.0, 0.0, 1.0, zAxis); // blue

    if (xAxis > 0.0)
    {
        Color.rgb = mix(Color.rgb, xColor.rgb, xAxis);
        Color.a = max(Color.a, xAxis);
    }

    if (zAxis > 0.0)
    {
        Color.rgb = mix(Color.rgb, zColor.rgb, zAxis);
        Color.a = max(Color.a, zAxis);
    }
    float OpacityFalloff = (1.0 - satf(length(vWorldPos.xz - vViewWorldPos.xz) / vGridSize));
    Color.a *= OpacityFalloff;
    FragColor = Color;
}