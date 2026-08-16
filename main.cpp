#include <windows.h>
#include <GL/glut.h>
#include <math.h>



// Sun/moon/flag circle
void drawCircle(float cx, float cy, float rad, int seg) {
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < seg; i++) {
        float angle = 2.0f * 3.1416f * i / seg;
        glVertex2f(cx + rad * cos(angle), cy + rad * sin(angle));
    }
    glEnd();
}
//---Ground-----
void drawGround(float x, float y, float width, float height) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f); // Shifts the ground to your X and Y position

     glColor3f(0.3f, 0.7f, 0.2f);


    glBegin(GL_QUADS);
        glVertex2f(-width / 2.0f,  0.0f);   //  T-Left
        glVertex2f( width / 2.0f,  0.0f);   // T- Right
        glVertex2f( width / 2.0f, -height); // B Right
        glVertex2f(-width / 2.0f, -height); // B Left
    glEnd();

    glPopMatrix();
}

void drawRiver(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

     glColor3f(0.2f, 0.5f, 0.8f);


    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.6f);
        glVertex2f( 1.0f, -0.6f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
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
        glVertex2f(x - 0.01f, y - 0.02f);
         glVertex2f(x + 0.13f, y - 0.02f);
        glVertex2f(x + 0.13f, y);
       glVertex2f(x - 0.01f, y);
    glEnd();
}

// 3. Grass
void drawGrass(float x, float y) {
    glColor3f(0.25f, 0.5f, 0.15f);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - 0.015f, y + 0.03f);
        glVertex2f(x, y);
         glVertex2f(x, y + 0.035f);
        glVertex2f(x, y);
        glVertex2f(x + 0.015f, y + 0.03f);
    glEnd();
}



// 4. Background mountain
void drawMountain(float width, float height) {

    glColor3f(0.4f, 0.5f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-width / 2.0f, 0.0f);
        glVertex2f( width / 2.0f, 0.0f);
        glVertex2f( 0.0f, height);
    glEnd();
}


// 5. Tree
void drawTree(float x, float y, float scale) {
     glColor3f(0.4f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y);
        glVertex2f(x + 0.02f*scale, y + 0.15f*scale);
          glVertex2f(x - 0.02f*scale, y + 0.15f*scale);
    glEnd();

    glColor3f(0.15f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.08f*scale, y + 0.1f*scale);
         glVertex2f(x + 0.08f*scale, y + 0.1f*scale);
          glVertex2f(x, y + 0.25f*scale);
        glVertex2f(x - 0.07f*scale, y + 0.18f*scale);
         glVertex2f(x + 0.07f*scale, y + 0.18f*scale);
          glVertex2f(x, y + 0.32f*scale);
        glVertex2f(x - 0.06f*scale, y + 0.25f*scale);
         glVertex2f(x + 0.06f*scale, y + 0.25f*scale);
          glVertex2f(x, y + 0.4f*scale);
    glEnd();
}

void drawRoundTree(float x, float y, float scale) {

    glColor3f(0.40f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.03f*scale, y);                     glVertex2f(x + 0.03f*scale, y);
        glVertex2f(x + 0.03f*scale, y + 0.22f*scale);       glVertex2f(x - 0.03f*scale, y + 0.22f*scale);
    glEnd();


    glColor3f(0.20f, 0.60f, 0.25f);

    // Bottom-Left
    glBegin(GL_QUADS);
        glVertex2f(x - 0.18f*scale, y + 0.16f*scale);
         glVertex2f(x - 0.02f*scale, y + 0.16f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.32f*scale);
         glVertex2f(x - 0.18f*scale, y + 0.32f*scale);
    glEnd();

    // Bottom-Right
    glBegin(GL_QUADS);
        glVertex2f(x + 0.02f*scale, y + 0.16f*scale);
         glVertex2f(x + 0.18f*scale, y + 0.16f*scale);
        glVertex2f(x + 0.18f*scale, y + 0.32f*scale);
         glVertex2f(x + 0.02f*scale, y + 0.32f*scale);
    glEnd();

    // Center round
    glBegin(GL_QUADS);
        glVertex2f(x - 0.12f*scale, y + 0.22f*scale);
         glVertex2f(x + 0.12f*scale, y + 0.22f*scale);
        glVertex2f(x + 0.12f*scale, y + 0.40f*scale);
        glVertex2f(x - 0.12f*scale, y + 0.40f*scale);
    glEnd();

    // top round
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.08f*scale, y + 0.40f*scale);
        glVertex2f(x + 0.08f*scale, y + 0.40f*scale);
        glVertex2f(x,                y + 0.48f*scale);
    glEnd();
}




// 7. TubeWell
void drawTubeWell(float x, float y) {
     glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.04f, y); glVertex2f(x + 0.04f, y);
        glVertex2f(x + 0.04f, y + 0.02f); glVertex2f(x - 0.04f, y + 0.02f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
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




// 9. Standard House
void drawVillageHouse(float x, float y, float scale) {
    glColor3f(0.45f, 0.35f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y);
        glVertex2f(x + 0.22f*scale, y);
        glVertex2f(x + 0.22f*scale, y + 0.04f*scale);
        glVertex2f(x - 0.02f*scale, y + 0.04f*scale);
    glEnd();

    glColor3f(0.85f, 0.75f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.04f*scale);
        glVertex2f(x + 0.2f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.2f*scale, y + 0.18f*scale);
        glVertex2f(x, y + 0.18f*scale);
    glEnd();

    glColor3f(0.7f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.03f*scale, y + 0.18f*scale);
        glVertex2f(x + 0.23f*scale, y + 0.18f*scale);
        glVertex2f(x + 0.1f*scale, y + 0.28f*scale);
    glEnd();

    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.08f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.12f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.12f*scale, y + 0.12f*scale);
        glVertex2f(x + 0.08f*scale, y + 0.12f*scale);
    glEnd();

    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x + 0.02f*scale, y + 0.08f*scale);
         glVertex2f(x + 0.06f*scale, y + 0.08f*scale);
        glVertex2f(x + 0.06f*scale, y + 0.12f*scale);
          glVertex2f(x + 0.02f*scale, y + 0.12f*scale);
    glEnd();
}



// 10. Toilet
void drawVillage_toilet(float x, float y, float scale) {
    glColor3f(0.45f, 0.35f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.02f*scale, y); glVertex2f(x + 0.18f*scale, y);
        glVertex2f(x + 0.18f*scale, y + 0.04f*scale); glVertex2f(x - 0.02f*scale, y + 0.04f*scale);
    glEnd();

    glColor3f(0.80f, 0.70f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.04f*scale); glVertex2f(x + 0.16f*scale, y + 0.04f*scale);
        glVertex2f(x + 0.16f*scale, y + 0.26f*scale); glVertex2f(x, y + 0.26f*scale);
    glEnd();

    glColor3f(0.6f, 0.3f, 0.2f);
    glBegin(GL_QUADS); // Chimney Stack
        glVertex2f(x + 0.1f*scale, y + 0.26f*scale); glVertex2f(x + 0.14f*scale, y + 0.26f*scale);
        glVertex2f(x + 0.14f*scale, y + 0.42f*scale); glVertex2f(x + 0.1f*scale, y + 0.42f*scale);
    glEnd();

    glColor3f(0.75f, 0.55f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.03f*scale, y + 0.26f*scale); glVertex2f(x + 0.19f*scale, y + 0.26f*scale); glVertex2f(x + 0.08f*scale, y + 0.36f*scale);
    glEnd();

    glColor3f(0.3f, 0.2f, 0.1f);
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

    //  Base
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.02f); glVertex2f(0.47f, -0.02f);
        glVertex2f(0.47f, 0.0f);    glVertex2f(-0.02f, 0.0f);
    glEnd();

    //  Side Wall
    glColor3f(0.85f, 0.75f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.25f, 0.0f);
        glVertex2f(0.25f, 0.15f); glVertex2f(0.0f, 0.15f);
    glEnd();

    // 3. Front Wall
    glColor3f(0.95f, 0.90f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.25f, 0.0f);  glVertex2f(0.45f, 0.0f);
        glVertex2f(0.45f, 0.15f); glVertex2f(0.25f, 0.15f);
    glEnd();

    //  Side Door
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0.09f, 0.0f);  glVertex2f(0.17f, 0.0f);
        glVertex2f(0.17f, 0.1f);  glVertex2f(0.09f, 0.1f);
    glEnd();

    // Front Window
    glBegin(GL_QUADS);
        glVertex2f(0.33f, 0.04f); glVertex2f(0.40f, 0.04f);
        glVertex2f(0.40f, 0.09f); glVertex2f(0.33f, 0.09f);
    glEnd();

    // 6. Side Roof
    glColor3f(0.7f, 0.45f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.15f); // Far left 
        glVertex2f( 0.20f, 0.15f); // Middle peak 
        glVertex2f( 0.35f, 0.28f); // Top peak left side
        glVertex2f( 0.10f, 0.28f); // Top peak far left
    glEnd();

    // 7. Front Roof
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

    // 1. Dark Brown Base
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.02f); glVertex2f(0.47f, -0.02f);
        glVertex2f(0.47f, 0.0f);    glVertex2f(-0.02f, 0.0f);
    glEnd();

    // 2. Front Wall
    glColor3f(0.95f, 0.90f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.2f, 0.0f);
        glVertex2f(0.2f, 0.15f); glVertex2f(0.0f, 0.15f);
    glEnd();

    // 3. Side Wall
    glColor3f(0.85f, 0.75f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(0.2f, 0.0f);  glVertex2f(0.45f, 0.0f);
        glVertex2f(0.45f, 0.15f); glVertex2f(0.2f, 0.15f);
    glEnd();

    // 4. Front Window
    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.04f); glVertex2f(0.12f, 0.04f);
        glVertex2f(0.12f, 0.09f); glVertex2f(0.05f, 0.09f);
    glEnd();

    // 5. Side Door
    glBegin(GL_QUADS);
        glVertex2f(0.28f, 0.0f);  glVertex2f(0.36f, 0.0f);
        glVertex2f(0.36f, 0.1f);  glVertex2f(0.28f, 0.1f);
    glEnd();

    // 6. Front Roof
    glColor3f(0.7f, 0.45f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, 0.15f); 
        glVertex2f( 0.25f, 0.15f); 
        glVertex2f( 0.10f, 0.28f); 
    glEnd();

    // 7. Side Roof
    glBegin(GL_QUADS);
        glVertex2f( 0.10f, 0.28f); 
        glVertex2f( 0.25f, 0.15f); 
        glVertex2f( 0.50f, 0.15f); 
        glVertex2f( 0.35f, 0.28f); 
    glEnd();

    glPopMatrix();
}

void drawRiversideHouse(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Wooden Stilts
    glColor3f(0.35f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        // Left stilt
        glVertex2f(0.02f, -0.15f); glVertex2f(0.05f, -0.15f);
        glVertex2f(0.05f,  0.0f);  glVertex2f(0.02f,  0.0f);
        // Right stilt
        glVertex2f(0.35f, -0.15f); glVertex2f(0.38f, -0.15f);
        glVertex2f(0.38f,  0.0f);  glVertex2f(0.35f,  0.0f);
    glEnd();

    // 2. Wooden Floor
    glColor3f(0.55f, 0.35f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.40f, 0.0f);
        glVertex2f(0.40f, 0.03f); glVertex2f(0.0f, 0.03f);
    glEnd();

    // 3. Main Cabin Walls
    glColor3f(0.80f, 0.68f, 0.50f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.03f);  glVertex2f(0.35f, 0.03f);
        glVertex2f(0.35f, 0.20f);  glVertex2f(0.05f, 0.20f);
    glEnd();

    // 4. Cabin Door
    glColor3f(0.35f, 0.2f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(0.12f, 0.03f);  glVertex2f(0.18f, 0.03f);
        glVertex2f(0.18f, 0.13f);  glVertex2f(0.12f, 0.13f);
    glEnd();

    // 5. Small Round Window
    glColor3f(0.35f, 0.2f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(0.24f, 0.10f);  glVertex2f(0.30f, 0.10f);
        glVertex2f(0.30f, 0.15f);  glVertex2f(0.24f, 0.15f);
    glEnd();

    // 6. Sloped Roof
    glColor3f(0.45f, 0.25f, 0.12f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.02f, 0.20f);  
        glVertex2f(0.38f, 0.20f);  
        glVertex2f(0.20f, 0.33f); 
    glEnd();

    glPopMatrix();
}

// 12. Paddy Storage
void drawPaddyStorage(float x, float y, float scale) {
    glColor3f(0.3f, 0.2f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x + 0.03f*scale, y);
        glVertex2f(x + 0.03f*scale, y + 0.06f*scale);
        glVertex2f(x + 0.07f*scale, y);
        glVertex2f(x + 0.07f*scale, y + 0.06f*scale);
        glVertex2f(x + 0.12f*scale, y);
        glVertex2f(x + 0.12f*scale, y + 0.06f*scale);
    glEnd();
    glLineWidth(1.0f);

     glColor3f(0.75f, 0.65f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(x, y + 0.06f*scale);
        glVertex2f(x + 0.15f*scale, y + 0.06f*scale);
        glVertex2f(x + 0.15f*scale, y + 0.2f*scale);
        glVertex2f(x, y + 0.2f*scale);
    glEnd();

    glColor3f(0.65f, 0.45f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.02f*scale, y + 0.2f*scale);
        glVertex2f(x + 0.17f*scale, y + 0.2f*scale);
        glVertex2f(x + 0.075f*scale, y + 0.28f*scale);
    glEnd();
}

//FLAG

void drawFlag(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Pole
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.17f);
    glEnd();

    // Cloth

glColor3f(0.0f, 0.42f, 0.24f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.17f);
        glVertex2f(0.1f, 0.15f);
        glVertex2f(0.1f, 0.09f);
        glVertex2f(0.0f, 0.07f);
    glEnd();
    //circle for flag

    glColor3f(0.86f,0.08f,0.24f);
    drawCircle(0.045f,0.12f,0.02f,30);

    glPopMatrix();
}



// 13. 3-Story School

void drawSchool(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 1. Left Building Block
    glColor3f(0.85f, 0.80f, 0.70f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(0.3f, 0.0f);
        glVertex2f(0.3f, 0.25f); glVertex2f(0.0f, 0.25f);
    glEnd();

    // 2. Right Building Block
    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.3f, 0.0f);  glVertex2f(0.85f, 0.0f);
        glVertex2f(0.85f, 0.5f); glVertex2f(0.3f, 0.5f);
    glEnd();

    // 3. Left Ledge
    glColor3f(0.35f, 0.35f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.25f); glVertex2f(0.32f, 0.25f);
        glVertex2f(0.32f, 0.28f);  glVertex2f(-0.02f, 0.28f);
    glEnd();

    //  Right
    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(0.28f, 0.5f);  glVertex2f(0.87f, 0.5f);
        glVertex2f(0.87f, 0.53f); glVertex2f(0.28f, 0.53f);
    glEnd();


    glColor3f(0.85f, 0.8f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(0.32f, 0.53f); glVertex2f(0.48f, 0.53f);
        glVertex2f(0.48f, 0.68f); glVertex2f(0.32f, 0.68f);
    glEnd();


    glColor3f(0.25f, 0.25f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(0.30f, 0.68f); glVertex2f(0.50f, 0.68f);
        glVertex2f(0.50f, 0.71f); glVertex2f(0.30f, 0.71f);
    glEnd();


    // 8. Flag
    drawFlag(0.8f, 0.53f, 1.0f);

    // 9. Windows
    glColor3f(0.5f, 0.7f, 0.9f);

    // Left Windows
  // LEFT BUILDING (2 Columns, 2 Rows)
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 2; col++) {

            float wx = 0.05f + (col * 0.10f); // Space between columns
            float wy = 0.05f + (row * 0.12f); // Space between rows

            glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.06f, wy);
                glVertex2f(wx + 0.06f, wy + 0.08f);
                glVertex2f(wx, wy + 0.08f);
            glEnd();
        }
    }

    // RIGHT BUILDING (4 Columns, 3 Rows)
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {

            float wx = 0.35f + (col * 0.12f); // Space between columns
            float wy = 0.05f + (row * 0.14f); // Space between rows

            glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.07f, wy);
                glVertex2f(wx + 0.07f, wy + 0.09f);
                glVertex2f(wx, wy + 0.09f);
            glEnd();
        }
    }

    glPopMatrix();
}


// Boat
void drawBoat(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // 1. stick
    glColor3f(0.7f, 0.7f, 0.4f);
    glBegin(GL_QUADS);

        glVertex2f(-0.18f, -0.05f); glVertex2f(-0.16f, -0.05f);
        glVertex2f(-0.16f,  0.10f); glVertex2f(-0.18f,  0.10f);
    glEnd();

    // 2. Rope
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
        glVertex2f(-0.17f, 0.03f); glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 3. Boat Hull
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.12f, 0.0f);  glVertex2f(0.12f, 0.0f);
        glVertex2f( 0.07f, -0.04f); glVertex2f(-0.07f, -0.04f);
    glEnd();

    // 4. Boat Cabin
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.0f);  glVertex2f(0.05f, 0.0f);
        glVertex2f( 0.05f, 0.07f); glVertex2f(-0.05f, 0.07f);
    glEnd();

    glPopMatrix();
}



void drawRoad() {

glColor3f(0.55f, 0.45f, 0.35f);

    glBegin(GL_QUAD_STRIP);

        // Start at the river
        glVertex2f( -0.1f, -0.60f); // Left
        glVertex2f( 0.3f, -0.60f); // Right

        // The sharp corner
        glVertex2f(-0.40f, -0.31f); // Left
        glVertex2f(-0.15f, -0.31f); // Right

        //  top right
        glVertex2f( 0.70f,  0.15f); // Left
        glVertex2f( 0.95f,  0.15f); // Right



    glEnd();
}



void display() {


    glClearColor(0.48f, 0.75f, 0.94f, 1.0f);


    glClear(GL_COLOR_BUFFER_BIT);

    // 2. DRAW THE BASE
    drawGround(0.0f, 0.4f,2.0f,1.0f);
    drawRiver(0.0f, 0.0f);


    drawRoad();
drawTree(0.4f, 0.1f, 0.6f);

//SUN
glColor3f(1.0f,0.85f,0.0f);
drawCircle(-0.9f,0.89f,0.065f,90);


//behind the mountain cloud
  drawCloud(0.64f,0.7f);


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

    //tree-1
    drawTree(0.9f, 0.06f, 0.9f);
    //tree-2
    drawTree(0.97f, 0.076f, 0.6f);

drawGrass(-0.0f,0.0f);
drawGrass(-0.1f,-0.3f);

     drawGrass(-0.2f, -0.15f);
    drawGrass(0.1f, -0.05f);
    drawGrass(0.45f, -0.25f);
    drawGrass(0.6f, -0.1f);
    drawGrass(-0.5f, 0.1f);
    drawGrass(-0.25f, 0.25f);
    drawGrass(-0.7f, -0.2f);
    drawGrass(0.5f, 0.15f);
    drawGrass(0.75f, -0.3f);
    drawGrass(-0.35f, -0.35f);
      drawGrass(-0.5f, -0.4f);
        drawGrass(-0.57f, -0.48f);
        drawGrass(-0.66f, -0.5f);
        drawGrass(-0.78f, -0.42f);
        drawGrass(-0.94f, -0.37f);
            drawGrass(-0.94f, -0.1f);





    //  6 Normal Trees
    for (int i = 0; i < 6; i++) {
       
        float posX = -0.95f + (i * 0.10f);
        float posY = 0.25f + ((i % 2) * 0.05f); // Slight height variation
        float scaleSize = 0.5f + ((i % 2) * 0.1f);

        drawTree(posX, posY, scaleSize);
    }

    // 2. Draw 4 Round Trees on left
    for (int i = 0; i < 4; i++) {
       
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
    drawSchool(0.2f, -0.2f, 0.75f);
    drawAngledHouseLeft(-0.4f,0.2f,0.5f);
     drawAngledHouseLeft(-0.1f,0.2f,0.4f);
      drawVillageHouseF(0.11f, 0.21f, 0.4f);
      drawAngledHouseRight(-0.04f,0.05f,0.5f);
      drawRiversideHouse(-0.4f,-0.56f,0.6f);

    drawBoat(0.0f, -0.61f);

    //Tubewell

    drawTubeWell(-0.6f,-0.1f);
    drawCloud(0.0f,0.8f);
     drawCloud(-0.6f,0.9f);
     drawCloud(0.64f,0.7f);


  
    glutSwapBuffers();
}



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


    glutMainLoop();
    return 0;
}
