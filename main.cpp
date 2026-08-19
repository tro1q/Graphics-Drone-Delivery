#include <windows.h>
#include <GL/glut.h>
#include <math.h>

//  Circle
void drawCircle(float cx, float cy, float rad, int seg) {
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < seg; i++) {
        float angle = 2.0f * 3.1416f * i / seg;
        glVertex2f(cx + rad * cos(angle), cy + rad * sin(angle));
    }
    glEnd();
}

// Ground
void drawGround(float x, float y, float width, float height) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.3f, 0.7f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-width / 2.0f,  0.0f);
        glVertex2f( width / 2.0f,  0.0f);
        glVertex2f( width / 2.0f, -height);
        glVertex2f(-width / 2.0f, -height);
    glEnd();
    glPopMatrix();
}

//  River
void drawRiver(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-100.0f, -60.0f);
        glVertex2f( 100.0f, -60.0f);
        glVertex2f( 100.0f, -100.0f);
        glVertex2f(-100.0f, -100.0f);
    glEnd();
    glPopMatrix();
}

//  Cloud
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 5.0f, 20);
    drawCircle(x + 6.0f, y + 2.0f, 6.5f, 20);
    drawCircle(x + 12.0f, y, 5.0f, 20);
}

//  Grass
void drawGrass(float x, float y) {
    glColor3f(0.25f, 0.5f, 0.15f);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x - 1.5f, y + 3.0f);
        glVertex2f(x, y);
        glVertex2f(x, y + 3.5f);
        glVertex2f(x, y);
        glVertex2f(x + 1.5f, y + 3.0f);
    glEnd();
}

// Background mountain
void drawMountain(float width, float height) {
    glColor3f(0.4f, 0.5f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-width / 2.0f, 0.0f);
        glVertex2f( width / 2.0f, 0.0f);
        glVertex2f( 0.0f, height);
    glEnd();
}

//  Small green hill for the base of the mountains
void drawFoothill(float width, float height) {
    glColor3f(0.25f, 0.6f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-width / 2.0f, 0.0f);
        glVertex2f( width / 2.0f, 0.0f);
        glVertex2f( 0.0f, height);
    glEnd();
}

//  Tree
void drawTree(float x, float y, float scale) {
    glPushMatrix();


    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);


    // Trunk
    glColor3f(0.4f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, 0.0f);
        glVertex2f( 2.0f, 0.0f);
        glVertex2f( 2.0f, 15.0f);
        glVertex2f(-2.0f, 15.0f);
    glEnd();

    // Leaves
    glColor3f(0.15f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
        // Bottom triangle
        glVertex2f(-8.0f, 10.0f);
        glVertex2f( 8.0f, 10.0f);
        glVertex2f( 0.0f, 25.0f);
        // Middle triangle
        glVertex2f(-7.0f, 18.0f);
        glVertex2f( 7.0f, 18.0f);
        glVertex2f( 0.0f, 32.0f);
        // Top triangle
        glVertex2f(-6.0f, 25.0f);
        glVertex2f( 6.0f, 25.0f);
        glVertex2f( 0.0f, 40.0f);
    glEnd();

    glPopMatrix(); 
}

//Round Tree
void drawRoundTree(float x, float y, float scale) {
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Draw the trunk 
    glColor3f(0.40f, 0.25f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-3.0f, 0.0f);
         glVertex2f( 3.0f, 0.0f);
        glVertex2f( 3.0f, 22.0f);
         glVertex2f(-3.0f, 22.0f);
    glEnd();

    glColor3f(0.20f, 0.60f, 0.25f);
    // Bottom-Left Leaves
    glBegin(GL_QUADS);
        glVertex2f(-18.0f, 16.0f);
        glVertex2f(-2.0f, 16.0f);

        glVertex2f(-2.0f, 32.0f);
         glVertex2f(-18.0f, 32.0f);
    glEnd();

    // Bottom-Right Leaves
    glBegin(GL_QUADS);
        glVertex2f( 2.0f, 16.0f);
        glVertex2f(18.0f, 16.0f);

        glVertex2f(18.0f, 32.0f);
         glVertex2f( 2.0f, 32.0f);
    glEnd();

    // Center round Leaves
    glBegin(GL_QUADS);
        glVertex2f(-12.0f, 22.0f);
        glVertex2f(12.0f, 22.0f);

        glVertex2f(12.0f, 40.0f);
        glVertex2f(-12.0f, 40.0f);
    glEnd();

    // Top round Leaves
    glBegin(GL_TRIANGLES);
        glVertex2f(-8.0f, 40.0f);
        glVertex2f( 8.0f, 40.0f);
        glVertex2f( 0.0f, 48.0f);
    glEnd();

    glPopMatrix();
}

//  TubeWell
void drawTubeWell(float x, float y) {
    glPushMatrix();


    glTranslatef(x, y, 0.0f);

    // Base
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-4.0f, 0.0f);
         glVertex2f( 4.0f, 0.0f);

        glVertex2f( 4.0f, 2.0f);
         glVertex2f(-4.0f, 2.0f);
    glEnd();

    // Main Pipe
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1.5f, 2.0f);
         glVertex2f( 1.5f, 2.0f);

        glVertex2f( 1.5f, 10.0f);
         glVertex2f(-1.5f, 10.0f);
    glEnd();

    // Handle
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 9.0f);
         glVertex2f(-8.0f, 13.0f);
    glEnd();
    glLineWidth(1.0f); // Always reset line width

    // Water Spout
    glBegin(GL_QUADS);
        glVertex2f(1.0f, 6.0f);
         glVertex2f(5.0f, 5.0f);

        glVertex2f(5.0f, 3.0f);
        glVertex2f(1.0f, 4.0f);
    glEnd();

    glPopMatrix();
}


//  Standard House
void drawVillageHouse(float x, float y, float scale) {
    glPushMatrix();


    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // House Base
    glColor3f(0.45f, 0.35f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, 0.0f);
         glVertex2f(22.0f, 0.0f);

        glVertex2f(22.0f, 4.0f);
         glVertex2f(-2.0f, 4.0f);
    glEnd();

    // Main Body
    glColor3f(0.85f, 0.75f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 4.0f);
        glVertex2f(20.0f, 4.0f);

        glVertex2f(20.0f, 18.0f);
         glVertex2f(0.0f, 18.0f);
    glEnd();

    // Roof
    glColor3f(0.7f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f, 18.0f);
        glVertex2f(23.0f, 18.0f);
        glVertex2f(10.0f, 28.0f);
    glEnd();

    // Door
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(8.0f, 4.0f);
        glVertex2f(12.0f, 4.0f);

        glVertex2f(12.0f, 12.0f);
        glVertex2f(8.0f, 12.0f);
    glEnd();

    // Window
      glColor3f(0.45f, 0.30f, 0.15f);

    glBegin(GL_QUADS);
        glVertex2f(2.0f, 8.0f);
         glVertex2f(6.0f, 8.0f);

        glVertex2f(6.0f, 12.0f);
         glVertex2f(2.0f, 12.0f);
    glEnd();

    glPopMatrix();
}

//  Toilet
void drawVillage_toilet(float x, float y, float scale) {
    glPushMatrix();


    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Base
    glColor3f(0.45f, 0.35f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, 0.0f);
         glVertex2f(18.0f, 0.0f);

        glVertex2f(18.0f, 4.0f);
         glVertex2f(-2.0f, 4.0f);
    glEnd();

    // Main Body
    glColor3f(0.80f, 0.70f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 4.0f);
         glVertex2f(16.0f, 4.0f);

        glVertex2f(16.0f, 26.0f);
        glVertex2f(0.0f, 26.0f);
    glEnd();

    // Chimney
    glColor3f(0.6f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(10.0f, 26.0f);
        glVertex2f(14.0f, 26.0f);

        glVertex2f(14.0f, 42.0f);
        glVertex2f(10.0f, 42.0f);
    glEnd();

    // Roof
    glColor3f(0.75f, 0.55f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-3.0f, 26.0f);
        glVertex2f(19.0f, 26.0f);
        glVertex2f(8.0f, 36.0f);
    glEnd();

    // Door
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(6.0f, 4.0f);
         glVertex2f(10.0f, 4.0f);

        glVertex2f(10.0f, 12.0f);
         glVertex2f(6.0f, 12.0f);
    glEnd();

    glPopMatrix();
}

//  Wide House
void drawVillageHouseF(float x, float y, float scale) {
    glPushMatrix();

    
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // House Base
    glColor3f(0.40f, 0.30f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, 0.0f);
        glVertex2f(32.0f, 0.0f);

        glVertex2f(32.0f, 4.0f);
         glVertex2f(-2.0f, 4.0f);
    glEnd();

    // Main House Body
    glColor3f(0.90f, 0.80f, 0.65f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 4.0f);
         glVertex2f(30.0f, 4.0f);

        glVertex2f(30.0f, 18.0f);
        glVertex2f(0.0f, 18.0f);
    glEnd();

    // Roof
    glColor3f(0.65f, 0.45f, 0.15f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-4.0f, 18.0f);
        glVertex2f(34.0f, 18.0f);
        glVertex2f(15.0f, 27.0f);
    glEnd();

    // Door
    glColor3f(0.3f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(13.0f, 4.0f);
         glVertex2f(17.0f, 4.0f);

        glVertex2f(17.0f, 12.0f);
        glVertex2f(13.0f, 12.0f);
    glEnd();

    glPopMatrix();
}

//  Angled House Right
void drawAngledHouseRight(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, -2.0f);
        glVertex2f(47.0f, -2.0f);

        glVertex2f(47.0f, 0.0f);
         glVertex2f(-2.0f, 0.0f);
    glEnd();

    glColor3f(0.85f, 0.75f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(25.0f, 0.0f);

        glVertex2f(25.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd();

    glColor3f(0.95f, 0.90f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(25.0f, 0.0f);
         glVertex2f(45.0f, 0.0f);

        glVertex2f(45.0f, 15.0f);
         glVertex2f(25.0f, 15.0f);
    glEnd();

    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(9.0f, 0.0f);
         glVertex2f(17.0f, 0.0f);

        glVertex2f(17.0f, 10.0f);
         glVertex2f(9.0f, 10.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(33.0f, 4.0f);
        glVertex2f(40.0f, 4.0f);

        glVertex2f(40.0f, 9.0f);
         glVertex2f(33.0f, 9.0f);
    glEnd();

    glColor3f(0.7f, 0.45f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(-5.0f, 15.0f);
        glVertex2f( 20.0f, 15.0f);

        glVertex2f( 35.0f, 28.0f);
         glVertex2f( 10.0f, 28.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f( 20.0f, 15.0f);
         glVertex2f( 50.0f, 15.0f);
          glVertex2f( 35.0f, 28.0f);
    glEnd();
    glPopMatrix();
}

//  Angled House Left
void drawAngledHouseLeft(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, -2.0f);
         glVertex2f(47.0f, -2.0f);

        glVertex2f(47.0f, 0.0f);
         glVertex2f(-2.0f, 0.0f);
    glEnd();

    glColor3f(0.95f, 0.90f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(20.0f, 0.0f);

        glVertex2f(20.0f, 15.0f);
        glVertex2f(0.0f, 15.0f);
    glEnd();

    glColor3f(0.85f, 0.75f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(20.0f, 0.0f);
        glVertex2f(45.0f, 0.0f);

        glVertex2f(45.0f, 15.0f);
         glVertex2f(20.0f, 15.0f);
    glEnd();

    glColor3f(0.5f, 0.3f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(5.0f, 4.0f);
         glVertex2f(12.0f, 4.0f);

        glVertex2f(12.0f, 9.0f);
        glVertex2f(5.0f, 9.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(28.0f, 0.0f);
         glVertex2f(36.0f, 0.0f);

        glVertex2f(36.0f, 10.0f);
        glVertex2f(28.0f, 10.0f);
    glEnd();

    glColor3f(0.7f, 0.45f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-5.0f, 15.0f);
         glVertex2f( 25.0f, 15.0f);
          glVertex2f( 10.0f, 28.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f( 10.0f, 28.0f);
        glVertex2f( 25.0f, 15.0f);

        glVertex2f( 50.0f, 15.0f);
         glVertex2f( 35.0f, 28.0f);
    glEnd();
    glPopMatrix();
}

// Riverside House
void drawRiversideHouse(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.35f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(2.0f, -15.0f);
        glVertex2f(5.0f, -15.0f);

        glVertex2f(5.0f,  0.0f);
        glVertex2f(2.0f,  0.0f);

        glVertex2f(35.0f, -15.0f);
        glVertex2f(38.0f, -15.0f);

        glVertex2f(38.0f,  0.0f);
         glVertex2f(35.0f,  0.0f);
    glEnd();

    glColor3f(0.55f, 0.35f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
          glVertex2f(40.0f, 0.0f);

        glVertex2f(40.0f, 3.0f);
         glVertex2f(0.0f, 3.0f);
    glEnd();

    glColor3f(0.80f, 0.68f, 0.50f);
    glBegin(GL_QUADS);
        glVertex2f(5.0f, 3.0f);
        glVertex2f(35.0f, 3.0f);

        glVertex2f(35.0f, 20.0f);
        glVertex2f(5.0f, 20.0f);
    glEnd();

    glColor3f(0.35f, 0.2f, 0.10f);
    glBegin(GL_QUADS);
        glVertex2f(12.0f, 3.0f);
         glVertex2f(18.0f, 3.0f);

        glVertex2f(18.0f, 13.0f);
         glVertex2f(12.0f, 13.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(24.0f, 10.0f);
         glVertex2f(30.0f, 10.0f);

        glVertex2f(30.0f, 15.0f);
          glVertex2f(24.0f, 15.0f);
    glEnd();

    glColor3f(0.45f, 0.25f, 0.12f);
    glBegin(GL_TRIANGLES);
        glVertex2f(2.0f, 20.0f);
        glVertex2f(38.0f, 20.0f);
        glVertex2f(20.0f, 33.0f);
    glEnd();
    glPopMatrix();
}

//  Paddy Storage
void drawPaddyStorage(float x, float y, float scale) {
    glPushMatrix();

    
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Legs (3 wooden posts)
    glColor3f(0.3f, 0.2f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(3.0f, 0.0f);
         glVertex2f(3.0f, 6.0f);

        glVertex2f(7.0f, 0.0f);
         glVertex2f(7.0f, 6.0f);

        glVertex2f(12.0f, 0.0f);
         glVertex2f(12.0f, 6.0f);
    glEnd();


    // Main Storage Body
    glColor3f(0.75f, 0.65f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 6.0f);
         glVertex2f(15.0f, 6.0f);

        glVertex2f(15.0f, 20.0f);
         glVertex2f(0.0f, 20.0f);
    glEnd();

    // Roof
    glColor3f(0.65f, 0.45f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-2.0f, 20.0f);
        glVertex2f(17.0f, 20.0f);
        glVertex2f(7.5f, 28.0f); // Peak
    glEnd();

    glPopMatrix();
}

//  Flag
void drawFlag(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 17.0f);
    glEnd();

    glColor3f(0.0f, 0.42f, 0.24f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 17.0f); glVertex2f(10.0f, 15.0f);
        glVertex2f(10.0f, 9.0f); glVertex2f(0.0f, 7.0f);
    glEnd();

    glColor3f(0.86f, 0.08f, 0.24f);
    drawCircle(4.5f, 12.0f, 2.0f, 30);
    glPopMatrix();
}

//  3-Story School
void drawSchool(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.85f, 0.80f, 0.70f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);  glVertex2f(30.0f, 0.0f);
        glVertex2f(30.0f, 25.0f); glVertex2f(0.0f, 25.0f);
    glEnd();

    glColor3f(0.9f, 0.85f, 0.75f);
    glBegin(GL_QUADS);
        glVertex2f(30.0f, 0.0f);  glVertex2f(85.0f, 0.0f);
        glVertex2f(85.0f, 50.0f); glVertex2f(30.0f, 50.0f);
    glEnd();

    glColor3f(0.35f, 0.35f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, 25.0f); glVertex2f(32.0f, 25.0f);
        glVertex2f(32.0f, 28.0f);  glVertex2f(-2.0f, 28.0f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(28.0f, 50.0f);  glVertex2f(87.0f, 50.0f);
        glVertex2f(87.0f, 53.0f); glVertex2f(28.0f, 53.0f);
    glEnd();

    glColor3f(0.85f, 0.8f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(32.0f, 53.0f); glVertex2f(48.0f, 53.0f);
        glVertex2f(48.0f, 68.0f); glVertex2f(32.0f, 68.0f);
    glEnd();

    glColor3f(0.25f, 0.25f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(30.0f, 68.0f); glVertex2f(50.0f, 68.0f);
        glVertex2f(50.0f, 71.0f); glVertex2f(30.0f, 71.0f);
    glEnd();

    drawFlag(80.0f, 53.0f, 1.0f);

    glColor3f(0.5f, 0.7f, 0.9f);
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 2; col++) {
            float wx = 5.0f + (col * 10.0f);
            float wy = 5.0f + (row * 12.0f);
            glBegin(GL_QUADS);
                glVertex2f(wx, wy); glVertex2f(wx + 6.0f, wy);
                glVertex2f(wx + 6.0f, wy + 8.0f); glVertex2f(wx, wy + 8.0f);
            glEnd();
        }
    }

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            float wx = 35.0f + (col * 12.0f);
            float wy = 5.0f + (row * 14.0f);
            glBegin(GL_QUADS);
                glVertex2f(wx, wy); glVertex2f(wx + 7.0f, wy);
                glVertex2f(wx + 7.0f, wy + 9.0f); glVertex2f(wx, wy + 9.0f);
            glEnd();
        }
    }
    glPopMatrix();
}

//  Fences around the school
void drawFence(float x, float y, float scale, float angle) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.55f, 0.35f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 12.0f);  glVertex2f(45.0f, 12.0f);
        glVertex2f(45.0f, 14.0f); glVertex2f(0.0f, 14.0f);
        glVertex2f(0.0f, 4.0f);  glVertex2f(45.0f, 4.0f);
        glVertex2f(45.0f, 6.0f); glVertex2f(0.0f, 6.0f);
    glEnd();

    float postX[3] = {5.0f, 22.5f, 40.0f};
    for(int i = 0; i < 3; i++) {
        float px = postX[i];

        // Base of the post
        glBegin(GL_QUADS);
            glVertex2f(px - 2.0f, 0.0f);  glVertex2f(px + 2.0f, 0.0f);
            glVertex2f(px + 2.0f, 18.0f); glVertex2f(px - 2.0f, 18.0f);
        glEnd();

        // Pointy triangle top of the post (Added this back so they look sharp!)
        glBegin(GL_TRIANGLES);
            glVertex2f(px - 2.0f, 18.0f);
            glVertex2f(px + 2.0f, 18.0f);
            glVertex2f(px, 22.0f);
        glEnd();
    }
    glPopMatrix();
}

//  Boat
void drawBoat(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.7f, 0.7f, 0.4f);
    glBegin(GL_QUADS);
        glVertex2f(-18.0f, -5.0f); glVertex2f(-16.0f, -5.0f);
        glVertex2f(-16.0f,  10.0f); glVertex2f(-18.0f,  10.0f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
        glVertex2f(-17.0f, 3.0f); glVertex2f(-8.0f, 0.0f);
    glEnd();

    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-12.0f, 0.0f);  glVertex2f(12.0f, 0.0f);
        glVertex2f( 7.0f, -4.0f); glVertex2f(-7.0f, -4.0f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-5.0f, 0.0f);  glVertex2f(5.0f, 0.0f);
        glVertex2f( 5.0f, 7.0f); glVertex2f(-5.0f, 7.0f);
    glEnd();

    glPopMatrix();
}

//  Road
void drawRoad() {
    glColor3f(0.55f, 0.45f, 0.35f);
    glBegin(GL_QUAD_STRIP);
        // Start at the river
        glVertex2f(-10.0f, -60.0f); // Left
        glVertex2f( 30.0f, -60.0f); // Right

        // The sharp corner
        glVertex2f(-40.0f, -31.0f); // Left
        glVertex2f(-15.0f, -31.0f); // Right

        // Top right
        glVertex2f( 70.0f,  15.0f); // Left
        glVertex2f( 95.0f,  15.0f); // Right
    glEnd();
}





void display() {


    glClearColor(0.48f, 0.75f, 0.94f, 1.0f);


    glClear(GL_COLOR_BUFFER_BIT);

    // 2. DRAW THE BASE
    drawGround(0.0f, 40.0f, 200.0f, 100.0f);
    drawRiver(0.0f, 0.0f);


    drawRoad();
drawTree(40.0f, 10.0f, 0.6f);

//SUN
glColor3f(1.0f,0.85f,0.0f);
drawCircle(-90.0f, 89.0f, 6.5f, 90);


//Tree nehind the cloud
 drawTree(63.0f, 57.0f, 0.3f);

//behind the mountain cloud
  drawCloud(64.0f, 70.0f);

  // house behind mountain

  drawVillageHouse(23.4f, 50.0f, 0.2f);


  //behind mountain tree

   drawTree(-90.0f, 60.0f, 0.3f);
   drawTree(-26.0f, 55.0f, 0.3f);
    drawTree(33.0f, 57.0f, 0.3f);

    //mountain-s1
    glPushMatrix();
    glTranslatef(-10.0f, 40.0f, 0.0f);
    drawMountain(50.0f, 40.0f);

    glPopMatrix();

     //mountain-s2
    glPushMatrix();
    glTranslatef(0.0f, 40.0f, 0.0f);
    drawMountain(70.0f, 40.0f);
      drawFoothill(40.0f, 7.0f);
    glPopMatrix();

     //mountain-l3
    glPushMatrix();
    glTranslatef(-40.0f, 40.0f, 0.0f);
    drawMountain(50.0f, 40.0f);
      drawFoothill(40.0f, 7.0f);
    glPopMatrix();

     //mountain-l4
    glPushMatrix();
    glTranslatef(-80.0f, 40.0f, 0.0f);
    drawMountain(50.0f, 40.0f);

    glPopMatrix();

       //mountain-l5
    glPushMatrix();
    glTranslatef(-97.0f, 40.0f, 0.0f);
    drawMountain(40.0f, 30.0f);
    glPopMatrix();


     //mountain-r6
    glPushMatrix();
    glTranslatef(40.0f, 40.0f, 0.0f);
    drawMountain(40.0f, 30.0f);
    drawFoothill(40.0f, 7.0f);

    glPopMatrix();
// house behind the right most hill
     drawVillageHouse(42.4f, 40.0f, 0.3f);

      //mountain-r7
    glPushMatrix();
    glTranslatef(80.0f, 40.0f, 0.0f);
    drawMountain(70.0f, 40.0f);
    drawFoothill(40.0f, 7.0f);
    glPopMatrix();

    // downhill details


    //tree-1
    drawTree(90.0f, 6.0f, 0.9f);
    //tree-2
    drawTree(97.0f, 7.6f, 0.6f);

drawGrass(-0.0f, 0.0f);
drawGrass(-10.0f, -30.0f);

     drawGrass(-20.0f, -15.0f);
    drawGrass(10.0f, -5.0f);
    drawGrass(45.0f, -25.0f);
    drawGrass(60.0f, -10.0f);
    drawGrass(-50.0f, 10.0f);
    drawGrass(-25.0f, 25.0f);
    drawGrass(-70.0f, -20.0f);
    drawGrass(50.0f, 15.0f);
    drawGrass(75.0f, -30.0f);
    drawGrass(-35.0f, -35.0f);
      drawGrass(-50.0f, -40.0f);
        drawGrass(-57.0f, -48.0f);
        drawGrass(-66.0f, -50.0f);
        drawGrass(-78.0f, -42.0f);
        drawGrass(-94.0f, -37.0f);
            drawGrass(-94.0f, -10.0f);






// Normal Trees on left
    drawTree(-95.0f, 25.0f, 0.5f);
    drawTree(-85.0f, 30.0f, 0.6f);
    drawTree(-75.0f, 25.0f, 0.5f);
    drawTree(-65.0f, 30.0f, 0.6f);
    drawTree(-55.0f, 25.0f, 0.5f);
    drawTree(-45.0f, 30.0f, 0.6f);

    // 4 Round Trees on left
    drawRoundTree(-90.0f, 32.0f, 0.55f);
    drawRoundTree(-78.0f, 28.0f, 0.55f);
    drawRoundTree(-66.0f, 32.0f, 0.55f);
    drawRoundTree(-54.0f, 28.0f, 0.55f);


 // 4 Round Trees on left
    drawRoundTree(-90.0f, 32.0f, 0.55f);
    drawRoundTree(-78.0f, 28.0f, 0.55f);
    drawRoundTree(-66.0f, 32.0f, 0.55f);
    drawRoundTree(-54.0f, 28.0f, 0.55f);

  drawTree(-80.0f, 10.0f, 1.0f);
  drawRoundTree(-60.0f, 30.0f, 0.5f);
      drawTree(-70.0f, 30.0f, 0.6f);

    //farone paddyStorage
    drawPaddyStorage(-10.0f, 30.0f, 0.3f);

    //leftone paddyStorage
     drawPaddyStorage(-48.0f, -6.0f, 0.7f);

    drawVillage_toilet(-90.0f, -10.0f, 0.6f);
     drawVillage_toilet(-15.0f, 26.0f, 0.3f);

    drawVillageHouseF(-30.0f, -10.0f, 0.8f);

    drawSchool(20.0f, -20.0f, 0.75f);
    //Fenches

  // down to river
    drawFence(-10.0f, -33.0f, 0.3f, -34.0f);
    drawFence( 1.2f, -40.5f, 0.3f, -34.0f);
    drawFence( 12.4f, -48.0f, 0.3f, -34.0f);
    drawFence( 20.0f, -53.0f, 0.3f, -34.0f); // Touches the river

    // Curve fence
    drawFence(-10.0f, -33.0f, 0.3f, 25.0f);
    drawFence( 2.2f, -27.3f, 0.3f, 10.0f);

    //  Horizontal Field Fence

    drawFence( 15.5f, -25.0f, 0.3f, 0.0f);
    drawFence( 29.0f, -25.0f, 0.3f, 0.0f);
    drawFence( 42.5f, -25.0f, 0.3f, 0.0f);
    drawFence( 56.0f, -25.0f, 0.3f, 0.0f);
    drawFence( 69.5f, -25.0f, 0.3f, 0.0f); //school end fence
      drawFence( 84.0f, 2.4f, 0.4f, 0.0f); //behind school fence

      //Near(linear to river)
       drawFence( 29.0f, -60.0f, 0.3f, 0.0f);
       drawFence( 42.5f, -60.0f, 0.3f, 0.0f);
        drawFence( 56.0f, -60.0f, 0.3f, 0.0f);
        drawFence( 69.5f, -60.0f, 0.3f, 0.0f);
      drawFence( 84.0f, -60.0f, 0.3f, 0.0f);

    drawAngledHouseLeft(-40.0f, 20.0f, 0.5f);
     drawAngledHouseLeft(-10.0f, 20.0f, 0.4f);
//windowHouse
     drawVillageHouse(11.0f, 21.0f, 0.5f);

      drawAngledHouseRight(-4.0f, 5.0f, 0.5f);
      drawRiversideHouse(-40.0f, -56.0f, 0.6f);

    drawBoat(0.0f, -61.0f);

    //Tubewell

    drawTubeWell(-60.0f, -10.0f);
    drawCloud(0.0f, 80.0f);
     drawCloud(-60.0f, 90.0f);

    // 5. SHOW ON SCREEN
    glutSwapBuffers();
}



void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
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
