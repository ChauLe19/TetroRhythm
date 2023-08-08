varying vec4 vColor;
varying vec2 vTexCoord;

uniform vec2 screenSize;

uniform sampler2D u_texture;
uniform vec4 v_time;

const float RADIUS = 0.75;

const float SOFTNESS = 0.6;

const float blurSize = 1.0/1000.0;

void main() {

    vec4 texColor = vec4(0.0); // texture2D(u_texture, vTexCoord)
    texColor += texture2D(u_texture, vTexCoord - 4.0*blurSize) * 0.05;
    texColor += texture2D(u_texture, vTexCoord - 3.0*blurSize) * 0.09;
    texColor += texture2D(u_texture, vTexCoord - 2.0*blurSize) * 0.12;
    texColor += texture2D(u_texture, vTexCoord - blurSize) * 0.15;
    texColor += texture2D(u_texture, vTexCoord) * 0.16;
    texColor += texture2D(u_texture, vTexCoord + blurSize) * 0.15;
    texColor += texture2D(u_texture, vTexCoord + 2.0*blurSize) * 0.12;
    texColor += texture2D(u_texture, vTexCoord + 3.0*blurSize) * 0.09;
    texColor += texture2D(u_texture, vTexCoord + 4.0*blurSize) * 0.05;

    vec4 timedColor = (vColor + v_time);

    vec2 position = (gl_FragCoord.xy / screenSize.xy) - vec2(0.5);
    float len = length(position);

    float vignette = smoothstep(RADIUS, RADIUS-SOFTNESS, len);

    texColor.rgb = mix(texColor.rgb, texColor.rgb * vignette, 0.5);

    gl_FragColor = vec4(texColor.rgb * timedColor.rgb, texColor.a);
}