#include <windows.h>
#include <GL/glut.h>
#include <math.h>

// =========================================================
// REQUIRED GLOBAL VARIABLES FOR COMPONENTS
// =========================================================
int isDay = 1;          // Required for day/night colors
float propAngle = 0.0f; // Required to spin the Drone propellers
float animTime = 0.0f;  // Required for the school flag waving animation

// =========================================================
// REUSABLE DRAWING COMPONENTS (SCENE 3)
// =========================================================

// 1. Core Helper
void drawCircle(float cx, float cy, float radius, int segments) {
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < segments; i++) {
        float angle = 2.0f * 3.1416f * i / segments;
        glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));
    }
    glEnd();
}
//---Ground-----
void drawGround(float x, float y, float width, float height) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // Shifts the ground to your X and Y position

    if (isDay) glColor3f(0.3f, 0.7f, 0.2f); // Bright green grass
    else glColor3f(0.15f, 0.35f, 0.1f);     // Dark green grass

    glBegin(GL_QUADS);
        glVertex2f(-width / 2.0f,  0.0f);   // Top Left
        glVertex2f( width / 2.0f,  0.0f);   // Top Right
        glVertex2f( width / 2.0f, -height); // Bottom Right
        glVertex2f(-width / 2.0f, -height); // Bottom Left
    glEnd();

    glPopMatrix();
}

void drawRiver(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // This shifts the river based on your parameters

    if (isDay) glColor3f(0.2f, 0.5f, 0.8f); // Blue water
    else glColor3f(0.1f, 0.25f, 0.4f);      // Dark blue water

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.6f); // Top Left of the water
        glVertex2f( 1.0f, -0.6f); // Top Right of the water
        glVertex2f( 1.0f, -1.0f); // Bottom Right
        glVertex2f(-1.0f, -1.0f); // Bottom Left
    glEnd();

    glPopMatrix();
}

// 2. Cloud
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.05f, 20);
    drawCircle(x + 0.06f, y + 0.02f, 0.065f, 20);
    drawCircle(x + 0.12f, y, 0.05f, 20);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.01f, y - 0.02f); glVertex2f(x + 0.13f, y - 0.02f);
        glVertex2f(x + 0.13f, y);         glVertex2f(x - 0.01f, y);
    glEnd();
}

// 3. Grass Tuft
void drawGrass(float x, float y) {
    if(isDay) glColor3f(0.25f, 0.5f, 0.15f); else glColor3f(0.1f, 0.25f, 0.1f);
    glBegin(GL_LINES);
        glVertex2f(x, y); glVertex2f(x - 0.015f, y + 0.03f);
        glVertex2f(x, y); glVertex2f(x, y + 0.035f);
        glVertex2f(x, y); glVertex2f(x + 0.015f, y + 0.03f);
    glEnd();
}

// 4. Background mountain
void drawMountain(float width, float height) {
    // Look how clean this is! No push, pop, or translate.
    glColor3f(0.4f, 0.5f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-width / 2.0f, 0.0f);
        glVertex2f( width / 2.0f, 0.0f);
        glVertex2f( 0.0f, height);
    glEnd();
}


// 5. Tree
void drawTree(float x, float y, float scale) {
    if(isDay) glColor3f(0.4f, 0.25f, 0.15f); else glColor3f(0.2f, 0.1f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);                 glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.15f*scale);   glVertex2f(x - 0.02f*scale, y + 0.15f*scale);
    glEnd();

    if(isDay) glColor3f(0.15f, 0.5f, 0.2f); else glColor3f(0.05f, 0.25f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.08f*scale, y + 0.1f*scale); glVertex2f(x + 0.08f*scale, y + 0.1f*scale); glVertex2f(x, y + 0.25f*scale);
        glVertex2f(x - 0.07f*scale, y + 0.18f*scale); glVertex2f(x + 0.07f*scale, y + 0.18f*scale); glVertex2f(x, y + 0.32f*scale);
        glVertex2f(x - 0.06f*scale, y + 0.25f*scale); glVertex2f(x + 0.06f*scale, y + 0.25f*scale); glVertex2f(x, y + 0.4f*scale);
    glEnd();
}

void drawRoundTree(float x, float y, float scale) {
    // 1. Thick Trunk
    glColor3f(0.40f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.03f*scale, y);                     glVertex2f(x + 0.03f*scale, y);
        glVertex2f(x + 0.03f*scale, y + 0.22f*scale);       glVertex2f(x - 0.03f*scale, y + 0.22f*scale);
    glEnd();

    // 2. Fluffy Rounded Canopy (Using overlapping shapes to form a round crown)
    glColor3f(0.20f, 0.60f, 0.25f); // Vibrant green

    // Bottom-Left Lobe
    glBegin(GL_QUADS);
        glVertex2f(x - 0.18f*scale, y + 0.16f*scale); glVertex2f(x - 0.02f*scale, y + 0.16f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.32f*scale); glVertex2f(x - 0.18f*scale, y + 0.32f*scale);
    glEnd();

    // Bottom-Right Lobe
    glBegin(GL_QUADS);
        glVertex2f(x + 0.02f*scale, y + 0.16f*scale); glVertex2f(x + 0.18f*scale, y + 0.16f*scale);
        glVertex2f(x + 0.18f*scale, y + 0.32f*scale); glVertex2f(x + 0.02f*scale, y + 0.32f*scale);
    glEnd();

    // Center-High Dome (Removes the flat top and creates a rounded crown)
    glBegin(GL_QUADS);
        glVertex2f(x - 0.12f*scale, y + 0.22f*scale); glVertex2f(x + 0.12f*scale, y + 0.22f*scale);
        glVertex2f(x + 0.12f*scale, y + 0.40f*scale); glVertex2f(x - 0.12f*scale, y + 0.40f*scale);
    glEnd();

    // Absolute Top Peak Cap (Ensures a smooth, circular finish)
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.08f*scale, y + 0.40f*scale);
        glVertex2f(x + 0.08f*scale, y + 0.40f*scale);
        glVertex2f(x,                y + 0.48f*scale);
    glEnd();
}

// 6. Bamboo Property Fence
void drawBambooFence(float x, float y, float length) {
    float i;
    if(isDay) glColor3f(0.6f, 0.5f, 0.3f); else glColor3f(0.3f, 0.2f, 0.15f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for(i = x; i < x + length; i += 0.05f) {
        glVertex2f(i, y); glVertex2f(i, y + 0.08f);
        if (i + 0.05f <= x + length) {
            glVertex2f(i, y + 0.02f); glVertex2f(i + 0.05f, y + 0.06f);
            glVertex2f(i, y + 0.06f); glVertex2f(i + 0.05f, y + 0.02f);
        }
    }
    glEnd();
    glLineWidth(1.0f);
}

// 7. Village Hand Pump (Tube Well)
void drawTubeWell(float x, float y) {
    if(isDay) glColor3f(0.6f, 0.6f, 0.6f); else glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.04f, y); glVertex2f(x + 0.04f, y);
        glVertex2f(x + 0.04f, y + 0.02f); glVertex2f(x - 0.04f, y + 0.02f);
    glEnd();
    if(isDay) glColor3f(0.2f, 0.2f, 0.2f); else glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.015f, y + 0.02f); glVertex2f(x + 0.015f, y + 0.02f);
        glVertex2f(x + 0.015f, y + 0.1f); glVertex2f(x - 0.015f, y + 0.1f);
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x, y + 0.09f); glVertex2f(x - 0.08f, y + 0.13f);
    glEnd();
    glLineWidth(1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.01f, y + 0.06f); glVertex2f(x + 0.05f, y + 0.05f);
        glVertex2f(x + 0.05f, y + 0.03f); glVertex2f(x + 0.01f, y + 0.04f);
    glEnd();
}

// 8. Brick School Gate & Arch
void drawSchoolGate(float x, float y) {
    if(isDay) glColor3f(0.6f, 0.3f, 0.2f); else glColor3f(0.3f, 0.15f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.4f, y); glVertex2f(x - 0.1f, y);
        glVertex2f(x - 0.1f, y + 0.08f); glVertex2f(x - 0.4f, y + 0.08f);
        glVertex2f(x + 0.2f, y); glVertex2f(x + 0.6f, y);
        glVertex2f(x + 0.6f, y + 0.08f); glVertex2f(x + 0.2f, y + 0.08f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.41f, y + 0.08f); glVertex2f(x - 0.09f, y + 0.08f);
        glVertex2f(x - 0.09f, y + 0.09f); glVertex2f(x - 0.41f, y + 0.09f);
        glVertex2f(x + 0.19f, y + 0.08f); glVertex2f(x + 0.61f, y + 0.08f);
        glVertex2f(x + 0.61f, y + 0.09f); glVertex2f(x + 0.19f, y + 0.09f);
    glEnd();

    if(isDay) glColor3f(0.7f, 0.7f, 0.7f); else glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.1f, y); glVertex2f(x - 0.05f, y);
        glVertex2f(x - 0.05f, y + 0.22f); glVertex2f(x - 0.1f, y + 0.22f);
        glVertex2f(x + 0.15f, y); glVertex2f(x + 0.2f, y);
        glVertex2f(x + 0.2f, y + 0.22f); glVertex2f(x + 0.15f, y + 0.22f);
    glEnd();

    if(isDay) glColor3f(0.2f, 0.4f, 0.8f); else glColor3f(0.1f, 0.2f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.12f, y + 0.18f); glVertex2f(x + 0.22f, y + 0.18f);
        glVertex2f(x + 0.22f, y + 0.25f); glVertex2f(x - 0.12f, y + 0.25f);
    glEnd();
}

// 9. Standard House
void drawVillageHouse(float x, float y, float scale) {
    if(isDay) glColor3f(0.45f, 0.35f, 0.25f); else glColor3f(0.25f, 0.15f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y); glVertex2f(x + 0.22f*scale, y);
        glVertex2f(x + 0.22f*scale, y + 0.04f*scale); glVertex2f(x - 0.02f*scale, y + 0.04f*scale);
    glEnd();

    if(isDay) glColor3f(0.85f, 0.75f, 0.6f); else glColor3f(0.5f, 0.45f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.04f*scale); glVertex2f(x + 0.2f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.2f*scale, y + 0.18f*scale); glVertex2f(x, y + 0.18f*scale);
    glEnd();

    if(isDay) glColor3f(0.7f, 0.5f, 0.2f); else glColor3f(0.4f, 0.3f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.03f*scale, y + 0.18f*scale); glVertex2f(x + 0.23f*scale, y + 0.18f*scale); glVertex2f(x + 0.1f*scale, y + 0.28f*scale);
    glEnd();

    if(isDay) glColor3f(0.3f, 0.2f, 0.1f); else glColor3f(0.15f, 0.1f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.08f*scale, y + 0.04f*scale); glVertex2f(x + 0.12f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.12f*scale, y + 0.12f*scale); glVertex2f(x + 0.08f*scale, y + 0.12f*scale);
    glEnd();

    if(isDay) glColor3f(0.6f, 0.8f, 0.9f); else glColor3f(1.0f, 0.9f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.02f*scale, y + 0.08f*scale); glVertex2f(x + 0.06f*scale, y + 0.08f*scale);
        glVertex2f(x + 0.06f*scale, y + 0.12f*scale); glVertex2f(x + 0.02f*scale, y + 0.12f*scale);
    glEnd();
}



// 10. Tall House (With Chimney Base)
void drawVillage_toilet(float x, float y, float scale) {
    if(isDay) glColor3f(0.45f, 0.35f, 0.25f); else glColor3f(0.25f, 0.15f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y); glVertex2f(x + 0.18f*scale, y);
        glVertex2f(x + 0.18f*scale, y + 0.04f*scale); glVertex2f(x - 0.02f*scale, y + 0.04f*scale);
    glEnd();

    if(isDay) glColor3f(0.80f, 0.70f, 0.55f); else glColor3f(0.45f, 0.40f, 0.30f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.04f*scale); glVertex2f(x + 0.16f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.16f*scale, y + 0.26f*scale); glVertex2f(x, y + 0.26f*scale);
    glEnd();

    if(isDay) glColor3f(0.6f, 0.3f, 0.2f); else glColor3f(0.3f, 0.15f, 0.1f);
    glBegin(GL_QUADS); // Chimney Stack
        glVertex2f(x + 0.1f*scale, y + 0.26f*scale); glVertex2f(x + 0.14f*scale, y + 0.26f*scale);
        glVertex2f(x + 0.14f*scale, y + 0.42f*scale); glVertex2f(x + 0.1f*scale, y + 0.42f*scale);
    glEnd();

    if(isDay) glColor3f(0.75f, 0.55f, 0.25f); else glColor3f(0.45f, 0.35f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.03f*scale, y + 0.26f*scale); glVertex2f(x + 0.19f*scale, y + 0.26f*scale); glVertex2f(x + 0.08f*scale, y + 0.36f*scale);
    glEnd();

    if(isDay) glColor3f(0.3f, 0.2f, 0.1f); else glColor3f(0.15f, 0.1f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.06f*scale, y + 0.04f*scale); glVertex2f(x + 0.10f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.10f*scale, y + 0.12f*scale); glVertex2f(x + 0.06f*scale, y + 0.12f*scale);
    glEnd();
}

// 11. Wide House
void drawVillageHouseF(float x, float y, float scale) {
    // House Base
    glColor3f(0.40f, 0.30f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.32f*scale, y);
        glVertex2f(x + 0.32f*scale, y + 0.04f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.04f*scale);
    glEnd();

    // Main House Body
    glColor3f(0.90f, 0.80f, 0.65f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.04f*scale);
        glVertex2f(x + 0.3f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.3f*scale, y + 0.18f*scale);
        glVertex2f(x, y + 0.18f*scale);
    glEnd();

    // Roof
    glColor3f(0.65f, 0.45f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.04f*scale, y + 0.18f*scale);
        glVertex2f(x + 0.34f*scale, y + 0.18f*scale);
        glVertex2f(x + 0.15f*scale, y + 0.27f*scale);
    glEnd();

    // Door
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.13f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.17f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.17f*scale, y + 0.12f*scale);
        glVertex2f(x + 0.13f*scale, y + 0.12f*scale);
    glEnd();
}

void drawAngledHouseRight(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Dark Brown Base / Foundation strip
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.02f); glVertex2f(0.47f, -0.02f);
        glVertex2f(0.47f, 0.0f);    glVertex2f(-0.02f, 0.0f);
    glEnd();

    // 2. Side Wall (Now on the Left)
    glColor3f(0.85f, 0.75f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.25f, 0.0f);
        glVertex2f(0.25f, 0.15f); glVertex2f(0.0f, 0.15f);
    glEnd();

    // 3. Front Wall (Now on the Right)
    glColor3f(0.95f, 0.90f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.25f, 0.0f);  glVertex2f(0.45f, 0.0f);
        glVertex2f(0.45f, 0.15f); glVertex2f(0.25f, 0.15f);
    glEnd();

    // 4. Side Door (On the Left wall)
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0.09f, 0.0f);  glVertex2f(0.17f, 0.0f);
        glVertex2f(0.17f, 0.1f);  glVertex2f(0.09f, 0.1f);
    glEnd();

    // 5. Front Window (On the Right wall)
    glBegin(GL_QUADS);
        glVertex2f(0.33f, 0.04f); glVertex2f(0.40f, 0.04f);
        glVertex2f(0.40f, 0.09f); glVertex2f(0.33f, 0.09f);
    glEnd();

    // 6. Side Roof Slanted Part (Left side)
    glColor3f(0.7f, 0.45f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.15f); // Far left overhang
        glVertex2f( 0.20f, 0.15f); // Middle peak connection
        glVertex2f( 0.35f, 0.28f); // Top peak left side
        glVertex2f( 0.10f, 0.28f); // Top peak far left
    glEnd();

    // 7. Front Roof Triangle Part (Right side)
    glBegin(GL_TRIANGLES);
        glVertex2f( 0.20f, 0.15f); // Left of triangle
        glVertex2f( 0.50f, 0.15f); // Right of triangle
        glVertex2f( 0.35f, 0.28f); // Top peak
    glEnd();

    glPopMatrix();
}

//Left to rightVillag Hosue
void drawAngledHouseLeft(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Dark Brown Base / Foundation strip
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.02f); glVertex2f(0.47f, -0.02f);
        glVertex2f(0.47f, 0.0f);    glVertex2f(-0.02f, 0.0f);
    glEnd();

    // 2. Front Wall (Light Cream Color)
    glColor3f(0.95f, 0.90f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.2f, 0.0f);
        glVertex2f(0.2f, 0.15f); glVertex2f(0.0f, 0.15f);
    glEnd();

    // 3. Side Wall (Slightly Darker / Tan Color)
    glColor3f(0.85f, 0.75f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(0.2f, 0.0f);  glVertex2f(0.45f, 0.0f);
        glVertex2f(0.45f, 0.15f); glVertex2f(0.2f, 0.15f);
    glEnd();

    // 4. Front Window (Dark Brown)
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.04f); glVertex2f(0.12f, 0.04f);
        glVertex2f(0.12f, 0.09f); glVertex2f(0.05f, 0.09f);
    glEnd();

    // 5. Side Door (Dark Brown)
    glBegin(GL_QUADS);
        glVertex2f(0.28f, 0.0f);  glVertex2f(0.36f, 0.0f);
        glVertex2f(0.36f, 0.1f);  glVertex2f(0.28f, 0.1f);
    glEnd();

    // 6. Front Roof (Triangle - Brown)
    glColor3f(0.7f, 0.45f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, 0.15f); // Left overhang
        glVertex2f( 0.25f, 0.15f); // Right overhang
        glVertex2f( 0.10f, 0.28f); // Top peak
    glEnd();

    // 7. Side Roof (Slanted Quad - Brown)
    glBegin(GL_QUADS);
        glVertex2f( 0.10f, 0.28f); // Connects to top peak
        glVertex2f( 0.25f, 0.15f); // Connects to right overhang
        glVertex2f( 0.50f, 0.15f); // Back right overhang
        glVertex2f( 0.35f, 0.28f); // Back top peak
    glEnd();

    glPopMatrix();
}

void drawRiversideHouse(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Wooden Stilts / Posts (Dipping down into the riverbank/water)
    glColor3f(0.35f, 0.2f, 0.1f); // Dark wood color
    glBegin(GL_QUADS);
        // Left stilt
        glVertex2f(0.02f, -0.15f); glVertex2f(0.05f, -0.15f);
        glVertex2f(0.05f,  0.0f);  glVertex2f(0.02f,  0.0f);
        // Right stilt
        glVertex2f(0.35f, -0.15f); glVertex2f(0.38f, -0.15f);
        glVertex2f(0.38f,  0.0f);  glVertex2f(0.35f,  0.0f);
    glEnd();

    // 2. Wooden Floor / Dock Base
    glColor3f(0.55f, 0.35f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.40f, 0.0f);
        glVertex2f(0.40f, 0.03f); glVertex2f(0.0f, 0.03f);
    glEnd();

    // 3. Main Cabin Walls (Weathered wood / Tan tone)
    glColor3f(0.80f, 0.68f, 0.50f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.03f);  glVertex2f(0.35f, 0.03f);
        glVertex2f(0.35f, 0.20f);  glVertex2f(0.05f, 0.20f);
    glEnd();

    // 4. Cabin Door (Facing the water/front)
    glColor3f(0.35f, 0.2f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(0.12f, 0.03f);  glVertex2f(0.18f, 0.03f);
        glVertex2f(0.18f, 0.13f);  glVertex2f(0.12f, 0.13f);
    glEnd();

    // 5. Small Round Window (Cabin style)
    // We can use your drawCircle helper, or a small square window:
    glColor3f(0.35f, 0.2f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(0.24f, 0.10f);  glVertex2f(0.30f, 0.10f);
        glVertex2f(0.30f, 0.15f);  glVertex2f(0.24f, 0.15f);
    glEnd();

    // 6. Sloped Roof (Classic Cabin Roof - Dark Brown)
    glColor3f(0.45f, 0.25f, 0.12f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.02f, 0.20f);  // Left overhang
        glVertex2f(0.38f, 0.20f);  // Right overhang
        glVertex2f(0.20f, 0.33f);  // Roof peak
    glEnd();

    glPopMatrix();
}

// 12. Paddy Storage
void drawPaddyStorage(float x, float y, float scale) {
    if(isDay) glColor3f(0.3f, 0.2f, 0.1f); else glColor3f(0.15f, 0.1f, 0.05f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x + 0.03f*scale, y); glVertex2f(x + 0.03f*scale, y + 0.06f*scale);
        glVertex2f(x + 0.07f*scale, y); glVertex2f(x + 0.07f*scale, y + 0.06f*scale);
        glVertex2f(x + 0.12f*scale, y); glVertex2f(x + 0.12f*scale, y + 0.06f*scale);
    glEnd();
    glLineWidth(1.0f);

    if(isDay) glColor3f(0.75f, 0.65f, 0.35f); else glColor3f(0.4f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.06f*scale); glVertex2f(x + 0.15f*scale, y + 0.06f*scale);
        glVertex2f(x + 0.15f*scale, y + 0.2f*scale); glVertex2f(x, y + 0.2f*scale);
    glEnd();

    if(isDay) glColor3f(0.65f, 0.45f, 0.2f); else glColor3f(0.35f, 0.25f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.02f*scale, y + 0.2f*scale);
        glVertex2f(x + 0.17f*scale, y + 0.2f*scale);
        glVertex2f(x + 0.075f*scale, y + 0.28f*scale);
    glEnd();
}

// 13. 3-Story School
void drawSchool(float x, float y, float scale) {
    float rx, wy, wx;

    // Position and scale logic built directly into the function
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Left Building Block
    glColor3f(0.85f, 0.80f, 0.70f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f); glVertex2f(0.3f, 0.0f);
        glVertex2f(0.3f, 0.25f); glVertex2f(0.0f, 0.25f);
    glEnd();

    // 2. Right Building Block
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.3f, 0.0f); glVertex2f(0.85f, 0.0f);
        glVertex2f(0.85f, 0.5f); glVertex2f(0.3f, 0.5f);
    glEnd();

    // 3. Left Ledge
    glColor3f(0.35f, 0.35f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.25f); glVertex2f(0.32f, 0.25f);
        glVertex2f(0.32f, 0.28f); glVertex2f(-0.02f, 0.28f);
    glEnd();

    // 4. Right Ledge
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(0.28f, 0.5f); glVertex2f(0.87f, 0.5f);
        glVertex2f(0.87f, 0.53f); glVertex2f(0.28f, 0.53f);
    glEnd();

    // 5. Penthouse (Top room)
    glColor3f(0.85f, 0.8f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(0.32f, 0.53f); glVertex2f(0.48f, 0.53f);
        glVertex2f(0.48f, 0.68f); glVertex2f(0.32f, 0.68f);
    glEnd();

    // 6. Penthouse Roof
    glColor3f(0.25f, 0.25f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(0.30f, 0.68f); glVertex2f(0.50f, 0.68f);
        glVertex2f(0.50f, 0.71f); glVertex2f(0.30f, 0.71f);
    glEnd();

    // 7. Fences
    glColor3f(0.4f, 0.4f, 0.45f);
    glBegin(GL_LINES);
    for(rx = 0.02f; rx <= 0.28f; rx += 0.05f) {
        glVertex2f(rx, 0.28f); glVertex2f(rx, 0.35f);
    }
    glVertex2f(0.0f, 0.35f); glVertex2f(0.3f, 0.35f);
    for(rx = 0.52f; rx <= 0.85f; rx += 0.05f) {
        glVertex2f(rx, 0.53f); glVertex2f(rx, 0.60f);
    }
    glVertex2f(0.50f, 0.60f); glVertex2f(0.85f, 0.60f);
    glEnd();

    // 8. Static School Flag
    glColor3f(0.8f, 0.8f, 0.8f); // Pole
    glBegin(GL_LINES);
        glVertex2f(0.8f, 0.53f); glVertex2f(0.8f, 0.7f);
    glEnd();

    glColor3f(0.2f, 0.7f, 0.3f); // Cloth (Animation removed)
    glBegin(GL_POLYGON);
        glVertex2f(0.8f, 0.7f);
        glVertex2f(0.9f, 0.68f);
        glVertex2f(0.9f, 0.62f);
        glVertex2f(0.8f, 0.6f);
    glEnd();

    // 9. Windows
    glColor3f(0.5f, 0.7f, 0.9f);
    for(wy = 0.05f; wy < 0.2f; wy += 0.12f) { // Left Windows
        for(wx = 0.05f; wx < 0.25f; wx += 0.1f) {
            glBegin(GL_QUADS);
                glVertex2f(wx, wy); glVertex2f(wx + 0.06f, wy);
                glVertex2f(wx + 0.06f, wy + 0.08f); glVertex2f(wx, wy + 0.08f);
            glEnd();
        }
    }
    for(wy = 0.05f; wy < 0.45f; wy += 0.14f) { // Right Windows
        for(wx = 0.35f; wx < 0.8f; wx += 0.12f) {
            glBegin(GL_QUADS);
                glVertex2f(wx, wy); glVertex2f(wx + 0.07f, wy);
                glVertex2f(wx + 0.07f, wy + 0.09f); glVertex2f(wx, wy + 0.09f);
            glEnd();
        }
    }

    glPopMatrix();
}

// 14. Moored Boat
void drawBoat(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // 1. Shorter Mooring Stick / Pole (Dipping into the water)
    glColor3f(0.7f, 0.7f, 0.4f);
    glBegin(GL_QUADS);
        // Shortened the top and bottom bounds so the stick looks shorter
        glVertex2f(-0.18f, -0.05f); glVertex2f(-0.16f, -0.05f);
        glVertex2f(-0.16f,  0.10f); glVertex2f(-0.18f,  0.10f);
    glEnd();

    // 2. Rope connecting stick to boat
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
        glVertex2f(-0.17f, 0.03f); glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 3. Boat Hull (Wooden Base)
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.12f, 0.0f);  glVertex2f(0.12f, 0.0f);
        glVertex2f( 0.07f, -0.04f); glVertex2f(-0.07f, -0.04f);
    glEnd();

    // 4. Boat Cabin / Center Box
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.0f);  glVertex2f(0.05f, 0.0f);
        glVertex2f( 0.05f, 0.07f); glVertex2f(-0.05f, 0.07f);
    glEnd();

    glPopMatrix();
}

// 15. Medical Box
void drawMedicalBox(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f, y - 0.02f); glVertex2f(x + 0.02f, y - 0.02f);
        glVertex2f(x + 0.02f, y + 0.02f); glVertex2f(x - 0.02f, y + 0.02f);
    glEnd();
    glColor3f(0.9f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.005f, y - 0.015f); glVertex2f(x + 0.005f, y - 0.015f);
        glVertex2f(x + 0.005f, y + 0.015f); glVertex2f(x - 0.005f, y + 0.015f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(x - 0.015f, y - 0.005f); glVertex2f(x + 0.015f, y - 0.005f);
        glVertex2f(x + 0.015f, y + 0.005f); glVertex2f(x - 0.015f, y + 0.005f);
    glEnd();
}

// 16. Drone
void drawDrone(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.22f, 0.22f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-0.035f, -0.012f); glVertex2f(0.035f, -0.012f);
        glVertex2f(0.035f, 0.012f);   glVertex2f(-0.035f, 0.012f);
    glEnd();

    glColor3f(1.0f, 0.1f, 0.1f); drawCircle(-0.02f, -0.014f, 0.005f, 10);
    glColor3f(0.1f, 0.9f, 0.2f); drawCircle(0.02f, -0.014f, 0.005f, 10);

    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.005f); glVertex2f(-0.03f, 0.005f);
        glVertex2f(-0.03f, 0.018f); glVertex2f(-0.05f, 0.018f);
        glVertex2f(0.03f, 0.005f); glVertex2f(0.05f, 0.005f);
        glVertex2f(0.05f, 0.018f); glVertex2f(0.03f, 0.018f);
    glEnd();

    glPushMatrix();
        glTranslatef(-0.04f, 0.02f, 0.0f); glRotatef(propAngle, 0.0f, 0.0f, 1.0f);
        glColor3f(0.8f, 0.8f, 0.85f);
        glBegin(GL_QUADS);
            glVertex2f(-0.025f, -0.003f); glVertex2f(0.025f, -0.003f);
            glVertex2f(0.025f, 0.003f);   glVertex2f(-0.025f, 0.003f);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.04f, 0.02f, 0.0f); glRotatef(propAngle, 0.0f, 0.0f, 1.0f);
        glColor3f(0.8f, 0.8f, 0.85f);
        glBegin(GL_QUADS);
            glVertex2f(-0.025f, -0.003f); glVertex2f(0.025f, -0.003f);
            glVertex2f(0.025f, 0.003f);   glVertex2f(-0.025f, 0.003f);
        glEnd();
    glPopMatrix();

    glPopMatrix();
}

void drawRoad() {

glColor3f(0.55f, 0.45f, 0.35f);
    // Using QUAD_STRIP is the professional way to draw roads and rivers!
    glBegin(GL_QUAD_STRIP);

        // Point 1: Start at the river
        glVertex2f( -0.1f, -0.60f); // Left edge of road
        glVertex2f( 0.3f, -0.60f); // Right edge of road

        // Point 2: The sharp '<' corner
        glVertex2f(-0.40f, -0.31f); // Left edge of road
        glVertex2f(-0.15f, -0.31f); // Right edge of road

        // Point 3: The long stretch up to the top right
        glVertex2f( 0.70f,  0.15f); // Left edge of road
        glVertex2f( 0.95f,  0.15f); // Right edge of road



    glEnd();
}

// =========================================================
// BASIC GLUT SETUP (Testing the components)
// =========================================================

void display() {
    // 1. CLEAR THE SCREEN FIRST (This paints the sky)
    if (isDay)
        glClearColor(0.48f, 0.75f, 0.94f, 1.0f);
    else
        glClearColor(0.06f, 0.08f, 0.18f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT); // The "eraser" goes here!

    // 2. DRAW THE BASE
    drawGround(0.0f, 0.4f,2.0f,1.0f);
    drawRiver(0.0f, 0.0f);

    drawRoad();
drawTree(0.4f, 0.1f, 0.6f);
    //mountain-s1
    glPushMatrix();
    glTranslatef(-0.1f,0.4f,0.0f);
    drawMountain(0.5f,0.4f);
    glPopMatrix();

     //mountain-s2
    glPushMatrix();
    glTranslatef(0.0f,0.4f,0.0f);
    drawMountain(0.7f,0.4f);
    glPopMatrix();

     //mountain-l3
    glPushMatrix();
    glTranslatef(-0.4f,0.4f,0.0f);
    drawMountain(0.5f,0.4f);
    glPopMatrix();

     //mountain-l4
    glPushMatrix();
    glTranslatef(-0.8f,0.4f,0.0f);
    drawMountain(0.5f,0.4f);
    glPopMatrix();

       //mountain-l5
    glPushMatrix();
    glTranslatef(-0.97f,0.4f,0.0f);
    drawMountain(0.4f,0.3f);
    glPopMatrix();


     //mountain-r6
    glPushMatrix();
    glTranslatef(0.4f,0.4f,0.0f);
    drawMountain(0.4f,0.3f);
    glPopMatrix();

      //mountain-r7
    glPushMatrix();
    glTranslatef(0.8f,0.4f,0.0f);
    drawMountain(0.7f,0.4f);
    glPopMatrix();

    //tree
    drawTree(0.9f, 0.06f, 0.9f);
    drawTree(0.97f, 0.076f, 0.6f);



    // 3. DRAW OBJECTS ON THE GRASS (Y should be between 0.2 and -0.6)



  // --- LEFT-SIDE JUNGLE (6 Normal Trees, 4 Round Trees) ---

    // 1. Draw 6 Normal Trees clustered on the left
    for (int i = 0; i < 6; i++) {
        // Stays strictly on the left side (X ranges from -0.95 to -0.45)
        float posX = -0.95f + (i * 0.10f);
        float posY = 0.25f + ((i % 2) * 0.05f); // Slight height variation
        float scaleSize = 0.5f + ((i % 2) * 0.1f);

        drawTree(posX, posY, scaleSize);
    }

    // 2. Draw 4 Round Trees clustered on the left
    for (int i = 0; i < 4; i++) {
        // Stays clustered on the left side, slightly behind/offset
        float posX = -0.90f + (i * 0.12f);
        float posY = 0.32f + ((i % 2) * -0.04f);
        float scaleSize = 0.55f;

        drawRoundTree(posX, posY, scaleSize);
    }

 drawTree(-0.8f, 0.1f, 1.0f);
  drawRoundTree(-0.6f,0.3f,0.5f);
      drawTree(-0.7f, 0.3f, 0.6f);

    //farone
    drawPaddyStorage(-0.1f,0.3f,0.3f);

    //leftone
     drawPaddyStorage(-0.48f,-0.06f,0.7f);

    drawVillage_toilet(-0.9f, -0.1f, 0.6f);
     drawVillage_toilet(-0.15f, 0.26f, 0.3f);
    drawVillageHouseF(-0.3f, -0.1f, 0.8f);
    drawSchool(0.2f, -0.2f, 0.75f); // I moved this up so it isn't underwater!
    drawAngledHouseLeft(-0.4f,0.2f,0.5f);
     drawAngledHouseLeft(-0.1f,0.2f,0.4f);
      drawVillageHouseF(0.11f, 0.21f, 0.4f);
      drawAngledHouseRight(-0.04f,0.05f,0.5f);
      drawRiversideHouse(-0.4f,-0.56f,0.6f);
    // 4. DRAW OBJECTS IN THE WATER (Y should be below -0.6)
    drawBoat(0.0f, -0.61f);

    // 5. SHOW ON SCREEN
    glutSwapBuffers();
}

/*void update(int value) {
    propAngle += 30.0f; // Spin drone propellers
    animTime += 0.05f;  // Wave the school flag

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'd' || key == 'D') isDay = 1;
    if (key == 'n' || key == 'N') isDay = 0;
    glutPostRedisplay();
}*/

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Scene 3 ");

    init();

    glutDisplayFunc(display);
   // glutKeyboardFunc(keyboard);
   // glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
