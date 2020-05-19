//EVERYTHING INCLUDING VECTOR MATHS AND CUSTOM PHYSICS WAS DONE BY FLUXO4, AKA PRASHANT KARN (076BEI026)
//Bzzt bzzt !#$^@#@ <Jackal !#$^ has enter-!#$^@#@-ed the room>?!#$^@#@
//Copyright (c) FLUXO4

#pragma region INCLUSIONS
#include <math.h>
//#include <stdlib.h>
//#include <stdarg.h>
#include <GL/glut.h>
//#include <stdio.h>
//#include <conio.h>
#include <stdbool.h>
#pragma endregion


#pragma region SETTINGS
bool startWithEasyMode = true;

//TIME AFTER WHICH A PLATFORM DISAPPEARS
int platformLife = 800;

//HOW QUICKLY THE APOCALYPSE TRAVELS
float apocaspeedd = 4;
#pragma endregion

#pragma region ONSCREENTEXT
//FOR PRINTING STRINGS ON THE SCREEN
void output(GLfloat x, GLfloat y, char* text)
{
    char* p;

    glPushMatrix();
    glTranslatef(x, y, 0);
    for (p = text; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
}
#pragma endregion

#pragma region VECTORMATHS
//               CUSTOM MATHS STRUCTS           - FluxO4(076BEI026)//
//Vector3
struct Vector3 {
    float x;
    float y;
    float z;
};


//Vector functions
struct Vector3 setVec(GLfloat x, GLfloat y, GLfloat z) {
    struct Vector3 t;
    t.x = x; t.y = y; t.z = z;
    return t;
}
float dot(struct Vector3 a, struct Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
struct Vector3 crs(struct Vector3 a, struct Vector3 b) {
    return setVec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
struct Vector3 add(struct Vector3 a, struct Vector3 b) {
    return setVec(a.x + b.x, a.y + b.y, a.z + b.z);
}
struct Vector3 rev(struct Vector3 a) {
    return setVec(-a.x, -a.y, -a.z);
}
float mag(struct Vector3 a) {
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}
struct Vector3 nor(struct Vector3 a) {
    float m = mag(a);
    return setVec(a.x / m, a.y / m, a.z / m);
}
struct Vector3 mul(float a, struct Vector3 b) {
    return setVec(a * b.x, a * b.y, a * b.z);
}
float angle(struct Vector3 a, struct Vector3 b) {
    return acos(dot(a, b) / (mag(a) * mag(b)));
}
struct Vector3 zero() {
    return setVec(0.0, 0.0, 0.0);
}
struct Vector3 project(struct Vector3 a, struct Vector3 target) {
    return mul(dot(a, target) / mag(target), nor(target));
}
struct Vector3 projectOnPlaneY(struct Vector3 a) {
    return setVec(a.x, 0.0, a.z);
}
float signedAngle(struct Vector3 a, struct Vector3 b, struct Vector3 up) {
    if (angle(crs(a, b), up) <= 3.14159) {
        return angle(a, b);
    }
    else {
        return -angle(a, b);
    }
}

#pragma endregion

#pragma region CONSTANTS
// --- CONSTANTS --- //

//Camera Average distance from player
float camDist = 5;
//Coefficient of parallel friction
float Cp = 0.95;
//Coefficient of normal friction
float Cn = 0.5;
//Coefficient of air resistance
float Ca = 0.99;
//Forward acceleration
float forAcc = 0.01f;
//Forward acceleration speed-up multiplier
float suM = 2;
//Gravitational acceleration
float gravAcc = -0.003f;

float jumpStrength = 0.12f;

float flyFactor = 0.5f;

//EASY MODE CONSTANTS
float e_Cp = 0.9f;
float e_forAcc = 0.03f;
float e_flyFactor = 0.16f;
float e_jumpStrength = 0.13f;
#pragma endregion

#pragma region VARIABLES_AND_OTHER
// --- CAMERA VECTORS --- //

//Camera Position vector
struct Vector3 cpos;
//Camera Forward vector
struct Vector3 cfor;

// --- PLAYER VECTORS --- //

//Player Position vector
struct Vector3 ppos;
//Player Forward vector
struct Vector3 pfor;
//Player Up vector
struct Vector3 pUp;
//player right vector;
struct Vector3 pRit;
//Player Velocity vector
struct Vector3 velocity;

// --- PLAYER PROPERTIES --- //
float playerColliderRadius = 0.5;
struct Vector3 playerHitBox;

// --- WORLD VECTORS --- //
//Y axis
struct Vector3 VecUp;

//gravity vector
struct Vector3 gravity;



//Player horizontal angle
float pangle = 0.0;

//Camera horizontal angle
float hangle = 0.0;
//Camera vertical angle
float vangle = 30.0;

float startx, starty;

float Zdelta = 0;

//TIME BEFORE PLATFORMS START THEIR LIFE CYCLE
int safeTime = 1000;

//IF SEED IS ANYTHING OTHER THAN 0, THE GAME WON'T BE RANDOMISED
float platformSeed = 0;
//TO GET THE INITIAL SEED IF platformSeed is 0
float randomiser = 0;
//PlayerColour, reddish, bright
static GLfloat playerColor[4] =
{ 1.3, 0.2, 0.0, 1.0 };

static GLfloat red[4] =
{ 0.8, 0.2, 0.0, 1.0 };

int score = 0;
int scoreOffset = 0;
//Key index
bool keypressed[6] = { false, false, false, false, false, false };
// 0 = Forward, 1 = backward, 2 = left, 3 = right, 4 = jump (Space), 5 = speed up (Ctrl)
bool easymode = false;

bool grounded = false;
bool mouseMoving = false;
bool groundedTest = false;
bool gamelost = false;

float apocaspeed;

int distanceCovered = 0;

int framecount;
#pragma endregion

#pragma region PLATFORMS

struct Platform {
    struct Vector3 pos;
    struct Vector3 size;
    int age;
};

//20 PLATFORMS TOTAL AT ANY INSTANT
struct Platform forms[20];

int numPlatforms = 20;

void createPlatform(struct Vector3 pos, struct Vector3 size) {
    if (numPlatforms < 20) {

        forms[numPlatforms].pos = pos;
        forms[numPlatforms].size = size;



        numPlatforms++;
    }
}

void createPlatformFor(struct Vector3 pos, struct Vector3 size, int index) {
    forms[index].pos = pos;
    forms[index].size = size;
    forms[index].age = 0;
}

void showPlatforms() {
    for (int i = 0; i < numPlatforms; i++) {
        static GLfloat pcolor[4] =
        { 0.0, 0.0, 0.0, 1.0 };
        pcolor[0] = 0.2 + forms[i].age / (platformLife * 0.8);
        if (pcolor[2] > 0.8) {
            pcolor[2] = 0.8;
        }
        pcolor[1] = 0.2;
        pcolor[2] = 0.2 + 1 - forms[i].age / (platformLife * 0.6);
        if (pcolor[2] < 0) {
            pcolor[2] = 0;
        }

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pcolor);
        //if (framecount > safeTime)
        {
            //forms[i].age == framecount + (int)forms[i].pos.z;
            //printf("%d \n", framecount);
            forms[i].age = framecount + (int)forms[i].pos.z / (0.1f * apocaspeed);

            if (forms[i].age < 0) {
                forms[i].age = 0;
            }
            if (forms[i].age > platformLife) {
                forms[i].pos.y = 20.0;
            }
        }

        glPushMatrix();
        glTranslatef(forms[i].pos.x, forms[i].pos.y, forms[i].pos.z);
        glScalef(forms[i].size.x, forms[i].size.y, forms[i].size.z);
        glutSolidCube(1);
        glPopMatrix();
    }
}


void createNextPlatform() {
    int d = ((int)(sqrt(platformSeed) * 100) % (10)) * 2;
    createPlatform(setVec(d, 0, -platformSeed * 8), setVec(3, 0.5, 5));
    platformSeed++;
}

void createNextPlatformFor(int index) {
    int d = ((int)(sqrt(platformSeed + randomiser) * 100) % (10)) * 2;
    int d2 = ((int)(sqrt(platformSeed + randomiser) * 1000) % (10)) * 2;
    int d3 = ((int)(sqrt(platformSeed + randomiser) * 10) % (10)) * 2;
    if (easymode) {
        createPlatformFor(setVec(d, d3 * 0.1f, -(platformSeed * 8 + d2)), setVec(6, 0.3, d2 + 3), index);
    }
    else {
        createPlatformFor(setVec(d, 0, -(platformSeed * 8 + d2)), setVec(3, 0.5, d2 + 3), index);
    }

    platformSeed++;

}


#pragma endregion

#pragma region COLLISION_PHYSICS
void addCollisionForce(struct Platform other) {
    if (mag(add(ppos, rev(setVec(other.pos.x, other.pos.y, other.pos.z - Zdelta)))) > (mag(playerHitBox) + mag(other.size))) {
        return;
    }
    float xx = 0, yy = 0, zz = 0;
    xx = fabs(ppos.x - other.pos.x) - fabs(playerHitBox.x * 0.5f + other.size.x * 0.5f);
    yy = fabs(ppos.y - other.pos.y) - fabs(playerHitBox.y * 0.5f + other.size.y * 0.5f);
    zz = fabs(ppos.z - other.pos.z + Zdelta) - fabs(playerHitBox.z * 0.5f + other.size.z * 0.5f);
    if (xx < 0 && yy < 0 && zz < 0) {
        int aa = maxof(xx, yy, zz);
        //printf("xx = %f , yy = %f , zz = %f  \n", xx, yy, zz);
        groundedTest = true;
        if (aa == 2) {
            velocity.y = 0;
            //grounded = true;
            if (ppos.y > other.pos.y) {
                ppos.y += -yy - 0.0001f;
                if (!grounded) {
                    groundedTest = true;
                    grounded = true;
                }
            }
            else {
                ppos.y += yy + 0.0001f;
                if (grounded) {
                    grounded = false;
                }
            }
        }
        else if (aa == 3) {
            //printf("groundedTest in the Z axis \n");
            velocity.z = 0;
            if (ppos.z > other.pos.z + Zdelta) {
                ppos.z += -zz - 0.0001f;
            }
            else {
                ppos.z += zz + 0.0001f;
            }
        }
        else if (aa == 1) {
            //printf("groundedTest in the X axis \n");
            velocity.x = 0;
            if (ppos.x > other.pos.x) {
                ppos.x += -xx - 0.0001f;
            }
            else {
                ppos.x += xx + 0.0001f;
            }
        }
    }
    else {
    }
}

int maxof(double a, double b, double c) {
    //printf("Comparing %f , %f , %f  \n", a, b, c );
    //printf("Max value ");
    if (a > b&& a > c) {

        //printf("%f \n", a);
        return 1;
    }
    else if (b > a&& b > c) {

        //printf("%f \n", b);
        return 2;
    }
    else if (c > a&& c > b) {

        //printf("%f \n", c);
        return 3;
    }
}
#pragma endregion

#pragma region HELPER_FUNCTIONS
void swap(float* a, float* b) {
    float t = *a;
    *a = *b;
    *b = t;
}

void varInit() {
    framecount = 0;
    //Player horizontal angle
    pangle = 0.0;
    distanceCovered = 0;
    //Camera horizontal angle
    hangle = 0.0;
    //Camera vertical angle
    vangle = 30.0;

    startx, starty;

    Zdelta = 0;

    scoreOffset = 0;
    score = 0;
    //TIME BEFORE PLATFORMS START THEIR LIFE CYCLE
    safeTime = 1000;

    //IF SEED IS ANYTHING OTHER THAN 0, THE GAME WON'T BE RANDOMISED
    platformSeed = 0;
    //TO GET THE INITIAL SEED IF platformSeed is 0
    randomiser = 0;

    keypressed[0] = false;
    keypressed[1] = false;
    keypressed[2] = false;
    keypressed[3] = false;
    keypressed[4] = false;
    keypressed[5] = false;

    easymode = false;

    grounded = false;
    mouseMoving = false;
    groundedTest = false;
    gamelost = false;

    platformLife = 800;

    apocaspeed = apocaspeedd;
}

void vectorInit() {

    velocity = zero();
    ppos = setVec(0.0f, 5.0f, 0.0f);
    pfor = setVec(0.0f, 0.0f, -1.0f);

    cpos.x = ppos.x - cfor.x * camDist;
    cpos.z = ppos.z - cfor.z * camDist;
    cpos.y = ppos.y + 1 - cfor.y * 3;

    VecUp = setVec(0.0, 1.0, 0.0);

    playerHitBox = setVec(0.5f, 1.2f, 0.5f);

    gravity = setVec(0.0, gravAcc, 0.0);
}

void vectorUpdate() {
    pfor.x = sin(pangle * 3.14159 / 180);
    pfor.z = -cos(pangle * 3.14159 / 180);

    pRit = nor(crs(VecUp, pfor));

    cfor.x = sin(hangle * 3.14159 / 180);
    cfor.z = -cos(hangle * 3.14159 / 180);

    cpos.x = ppos.x - cfor.x * camDist;
    cpos.z = ppos.z - cfor.z * camDist;
    cpos.y = ppos.y + 1 - cfor.y * 3;
}

void LookAt(struct Vector3 pos, struct Vector3 targetPos, struct Vector3 up) {
    gluLookAt(pos.x, pos.y, pos.z,
        targetPos.x, targetPos.y, targetPos.z,
        up.x, up.y, up.z);
}

void easy_mode() {
    if (!easymode) {
        easymode = true;
        swap(&Cp, &e_Cp);
        swap(&e_forAcc, &forAcc);
        swap(&e_flyFactor, &flyFactor);
        swap(&e_jumpStrength, &jumpStrength);


        platformSeed += -numPlatforms;
        for (int i = 0; i < numPlatforms; i++) {
            if (mag(add(forms[i].pos, rev(ppos))) > 10) {
                int d3 = ((int)(sqrt(platformSeed + randomiser) * 10) % (10)) * 2;
                platformSeed++;
                forms[i].pos.y = d3 * 0.1f;
                forms[i].size.x = 6;
                forms[i].size.y = 0.3;
            }
        }

    }
}

void hard_mode() {
    if (easymode) {
        easymode = false;
        swap(&Cp, &e_Cp);
        swap(&e_forAcc, &forAcc);
        swap(&e_flyFactor, &flyFactor);
        swap(&e_jumpStrength, &jumpStrength);
        for (int i = 0; i < numPlatforms; i++) {
            if (mag(add(forms[i].pos, rev(ppos))) > 10) {
                forms[i].pos.y = 0;
                forms[i].size.x = 3;
                forms[i].size.y = 0.5;
            }
        }
    }
}

static void init(void)
{
    static GLfloat pos[4] =
    { 5.0, 5.0, 10.0, 0.0 };


    vectorInit();
    varInit();
    if (startWithEasyMode) {
        easy_mode();
    }

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    time_t t;
    srand((unsigned)time(&t));
    randomiser = (rand() % 500) * 0.01f;

    createPlatformFor(setVec(0, 0, 0), setVec(6, 1, 6), 0);

    for (int i = 1; i < 20; i++) {
        createNextPlatformFor(i);
        //createPlatformFor(setVec(0, 0, -platformSeed * 8 ), setVec(3, 0.5, 5), i);
        platformSeed++;
    }

    showPlatforms;

    glEnable(GL_NORMALIZE);
}


#pragma endregion

#pragma region CHARACTER_MODEL
void createLeg() {

    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    glScalef(0.2, 0.2, 0.2);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glutSolidTetrahedron();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -0.125, 0.0);
    glScalef(0.2, 0.5, 0.2);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glutSolidTetrahedron();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

}

void createBody() {

    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    glScalef(0.2, 0.2, 0.4);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glutSolidTetrahedron();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -0.13, 0.0);
    glScalef(0.2, 0.5, 0.4);
    glRotatef(-90.0, 0.0, 0.0, 1.0);
    glutSolidTetrahedron();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

}

void createCharacter() {
    float animFactor = framecount * 0.2;
    if (keypressed[5]) {
        animFactor = animFactor * 2;
    }
    if (!grounded) {
        animFactor = animFactor * 2;
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, playerColor);

    glPushMatrix();
    if (grounded && (keypressed[0] || keypressed[1])) {
        glRotatef(40 * sin(animFactor), 1.0, 0.0, 0.0);
    }
    else if (!grounded && (keypressed[0] || keypressed[1])) {
        glRotatef(-50 + 40 * sin(animFactor), 1.0, 0.0, 0.0);
    }
    else if (!grounded) {
        glRotatef(-50, 1.0, 0.0, 0.0);
    }
    glPushMatrix();
    glTranslatef(0.2, 0.0, 0.0);
    glRotatef(5.0, 0.0, 0.0, 1.0);
    createLeg();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    if (grounded && (keypressed[0] || keypressed[1])) {
        glRotatef(-40 * sin(animFactor), 1.0, 0.0, 0.0);
    }
    else if (!grounded && (keypressed[0] || keypressed[1])) {
        glRotatef(-60 - 40 * sin(animFactor), 1.0, 0.0, 0.0);
    }
    else if (!grounded) {
        glRotatef(-60, 1.0, 0.0, 0.0);
    }
    glPushMatrix();
    glTranslatef(-0.2, 0.0, 0.0);
    glRotatef(-5.0, 0.0, 0.0, 1.0);
    createLeg();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    if (grounded && keypressed[0]) {
        glRotatef(-40 * sin(animFactor), 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, 0.55 * sin(animFactor));
    }
    else if (!grounded) {
        glRotatef(90, 0.0, 0.0, 1.0);
        glTranslatef(0.5, -1.15, 0.0);
    }
    glPushMatrix();
    glTranslatef(0.5, 0.65, 0.0);
    glScalef(0.6, 1.0, 0.6);
    glRotatef(30.0, 0.0, 0.0, 1.0);
    createLeg();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    if (grounded && keypressed[0]) {
        glRotatef(40 * sin(animFactor), 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, -0.55 * sin(animFactor));
    }
    else if (!grounded) {
        glRotatef(-90, 0.0, 0.0, 1.0);
        glTranslatef(-0.5, -1.15, 0.0);
    }
    glPushMatrix();
    glTranslatef(-0.5, 0.65, 0.0);
    glScalef(0.6, 1.0, 0.6);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    createLeg();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    if (grounded && keypressed[0]) {
        glTranslatef(0.0, 0.03 * sin(animFactor * 2.0), 0.0);
    }
    createBody();
    glPushMatrix();
    glTranslatef(0.0, 1.4, 0.0);
    glScalef(0.4, 0.4, 0.4);
    glutSolidIcosahedron();
    glPopMatrix();
    glPopMatrix();

}
#pragma endregion

#pragma region MAIN_LOOP_FUNCTIONS
void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    /*GLfloat pos[4] =
    { cpos.x + 5.0, cpos.x + 5.0, cpos.x + 10.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);*/

    LookAt(cpos, add(cpos, cfor), setVec(0.0f, 1.0f, 0.0f));

    // --- DEBUG CUBE --- //
    /*glPushMatrix();
    glTranslatef(ppos.x,ppos.y,ppos.z);
    glScalef(playerHitBox.x, playerHitBox.y, playerHitBox.z);
    glutWireCube(1);
    glPopMatrix();*/

    glPushMatrix();
    glTranslatef(ppos.x, ppos.y - 0.3f, ppos.z);
    glScalef(0.5f, 0.5f, 0.5f);
    if (!grounded) {
        glRotatef(-20, 1.0, 0.0, 0.0);
    }
    glPushMatrix();
    glRotatef(-pangle, 0.0, 1.0, 0.0);
    createCharacter();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -Zdelta);
    showPlatforms();
    glPopMatrix();

    framecount++;


    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1600, -900, 150);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //score = (int)(-Zdelta) + scoreOffset;
    char scorec[6];
    sprintf_s(scorec, 6, "%d", score);

    output(10, 10, scorec);

    if (ppos.y < -10.0) {
        output(200, -200, "OOPS! YOU FELL!");
        output(500, -700, "PRESS 'R'");
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);

    {
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 6400, -3600, 150);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        if (easymode) {
            output(4500, 10, "EASY");
        }
        else {
            output(4500, 10, "HARD (TOGGLE WITH 'M')");
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glPopAttrib();
        glMatrixMode(GL_MODELVIEW);
    }
    glutSwapBuffers();

}

void idleScene(void) {
    if (ppos.y < -40.0) {
        //Sleep(10);
        //printf("SCORE IS %d", (int)(-Zdelta));
        if (!gamelost) {
            gamelost = true;
        }

        return;
    }

    Sleep(20);
    //Keypresses

    if ((int)(-Zdelta) > distanceCovered) {
        if (easymode) {
            score = score + ((int)(-Zdelta) - distanceCovered);
        }
        else {
            if (framecount % 2 == 0) {
                score = score + (int)(((int)(-Zdelta) - distanceCovered) * 2);
            }
            else {
                score = score + (int)(((int)(-Zdelta) - distanceCovered));
            }
        }
        distanceCovered = (int)(-Zdelta);
    }

    if (framecount % 200 == 0 && platformLife > 400) {
        platformLife = (int)platformLife * (0.995f);
        apocaspeed = apocaspeed * (1.02f);
    }
    if (!easymode && framecount % 20 == 1) {
        scoreOffset += 1;
    }

    if (grounded) {
        float f = forAcc;
        if (keypressed[5]) {
            f = forAcc * suM;
        }

        if (keypressed[0]) {
            velocity.x += pfor.x * f;
            velocity.z += pfor.z * f;
        }
        else if (keypressed[1]) {
            velocity.x -= pfor.x * forAcc;
            velocity.z -= pfor.z * forAcc;
        }
    }
    else {
        if (keypressed[0]) {
            velocity.x += pfor.x * forAcc * flyFactor;
            velocity.z += pfor.z * forAcc * flyFactor;
        }
        else if (keypressed[1]) {
            velocity.x -= pfor.x * forAcc * flyFactor;
            velocity.z -= pfor.z * forAcc * flyFactor;
        }
    }



    if (keypressed[2]) {
        pangle -= 3;
    }
    else if (keypressed[3]) {
        pangle += 3;
    }




    //friction
    if (grounded) {
        struct Vector3 t2 = projectOnPlaneY(velocity);
        struct Vector3 t = add(mul(Cp, project(t2, pfor)), mul(Cn, project(t2, pRit)));
        velocity = setVec(t.x, velocity.y, t.z);
    }
    else {
        velocity = mul(Ca, velocity);
    }

    //collision
    for (int i = 0; i < numPlatforms; i++) {
        addCollisionForce(forms[i]);
    }

    for (int i = 0; i < numPlatforms; i++) {
        if (forms[i].pos.z - Zdelta > 40) {
            createNextPlatformFor(i);
            break;
        }
    }

    if (!groundedTest) {
        if (grounded) {
            grounded = false;
        }
    }
    else {
        groundedTest = false;
    }

    //jump and gravity
    if (grounded) {
        if (keypressed[4]) {
            if (keypressed[5]) {
                velocity.y = jumpStrength * 1.5f;;
            }
            else {
                velocity.y = jumpStrength;
            }
        }
    }
    else {
        velocity = add(velocity, gravity);
    }


    if (!mouseMoving) {
        if (fabs(pangle - hangle) > 0.5f)
            hangle = hangle + (pangle - hangle) * 0.1f;
    }

    vectorUpdate();

    //Velocity
    //ppos = add(ppos, velocity);
    //Velocity to centre z
    ppos = add(ppos, setVec(velocity.x, velocity.y, 0.0));
    Zdelta = Zdelta + velocity.z;

    glutPostRedisplay();
}
#pragma endregion

#pragma region MOUSE_AND_KEYS
void Keys(unsigned char key, int x, int y)
{
    if (glutGetModifiers())
    {
        if (GLUT_ACTIVE_SHIFT) {
            keypressed[5] = true;
        }
        else {
            keypressed[5] = false;
        }
    }
    else {
        keypressed[5] = false;
    }


    if (key == 'a' || key == 'A')
        keypressed[2] = true;
    //break;
    if (key == 'd' || key == 'D')
        keypressed[3] = true;
    //break;
    if (key == 'w' || key == 'W')
        keypressed[0] = true;
    //break;
    if (key == 's' || key == 'S') {
        keypressed[1] = true;
        keypressed[4] = false;
        keypressed[5] = false;
    }
    //break;
    if (key == ' ')
        keypressed[4] = true;
    //break;
    if (key == '0')
        keypressed[5] = true;
    //break;
    if (key == 'f')
        keypressed[5] = true;

    if (key == 'm') {
        if (!easymode) {
            easy_mode();
        }
        else {
            hard_mode();
        }
    }

    if (key == 'r') {
        if (ppos.y < -10) {
            init();
        }
    }

    if (key == 27) {
        exit(0);
    }

}

void SKeys(int key, int xx, int yy)
{
    if (glutGetModifiers())
    {
        if (GLUT_ACTIVE_SHIFT) {
            keypressed[5] = true;
        }
        else {
            keypressed[5] = false;
        }
    }
    else {
        keypressed[5] = false;
    }

    if (key == GLUT_KEY_LEFT) {
        keypressed[2] = true;
    }


    if (key == GLUT_KEY_RIGHT) {
        keypressed[3] = true;
    }

    if (key == GLUT_KEY_UP) {
        keypressed[0] = true;
    }

    if (key == GLUT_KEY_DOWN) {
        keypressed[1] = true;
        keypressed[4] = false;
        keypressed[5] = false;
    }
}

void KeysUp(unsigned char key, int xx, int yy) {
    if (glutGetModifiers())
    {
        if (GLUT_ACTIVE_SHIFT) {
            keypressed[5] = true;
        }
        else {
            keypressed[5] = false;
        }
    }
    else {
        keypressed[5] = false;
    }



    if (key == 'a' || key == 'A')
        keypressed[2] = false;
    //break;
    if (key == 'd' || key == 'D')
        keypressed[3] = false;
    //break;
    if (key == 'w' || key == 'W')
        keypressed[0] = false;
    //break;
    if (key == 's' || key == 'S') {
        keypressed[1] = false;
        keypressed[4] = false;
        keypressed[5] = false;
    }
    //break;
    if (key == ' ')
        keypressed[4] = false;
    //break;
    if (key == '0')
        keypressed[5] = false;
    //break;
    if (key == 'f')
        keypressed[5] = false;



}

void SKeysUp(int key, int xx, int yy) {
    if (glutGetModifiers())
    {
        if (GLUT_ACTIVE_SHIFT) {
            keypressed[5] = true;
        }
        else {
            keypressed[5] = false;
        }
    }
    else {
        keypressed[5] = false;
    }


    if (key == GLUT_KEY_LEFT) {
        keypressed[2] = false;
    }


    if (key == GLUT_KEY_RIGHT) {
        keypressed[3] = false;
    }

    if (key == GLUT_KEY_UP) {
        keypressed[0] = false;
    }

    if (key == GLUT_KEY_DOWN) {
        keypressed[1] = false;
        keypressed[4] = false;
        keypressed[5] = false;
    }
}

static void mouse(int button, int state, int x, int y)
{
    startx = x;
    starty = y;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {

            mouseMoving = true;
        }
        if (state == GLUT_UP) {
            mouseMoving = false;
        }
    }

    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            keypressed[4] = true;
        }
        if (state == GLUT_UP) {
            keypressed[4] = false;
        }
    }
}

static void motion(int x, int y) {
    if (mouseMoving) {
        hangle = hangle + (x - startx) / 2;
        vangle = vangle - (y - starty) / 2;
        /*if (hangle >= 180) { hangle = hangle - 180; }
        if (hangle < -180) { hangle = hangle + 180; }*/

        cfor.x = sin(hangle * 3.14159 / 180);
        cfor.z = -cos(hangle * 3.14159 / 180);
        cfor.y = sin(vangle * 3.14159 / 180);

        cpos.x = ppos.x - cfor.x * camDist;
        cpos.z = ppos.z - cfor.z * camDist;
        cpos.y = ppos.y + 1 - cfor.y * 3;
        //hangle2 = hangle2 + (y - starty) / 10;
        startx = x;
        starty = y;
    }

    glutPostRedisplay();
}
#pragma endregion

int main(int argc, char** argv)
{

    // init GLUT and create window

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(0, 20);
    glutInitWindowSize(1120, 630);
    glutCreateWindow("Sky-runner");


    init();
    glutIdleFunc(idleScene);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(Keys);
    glutSpecialFunc(SKeys);
    glutKeyboardUpFunc(KeysUp);
    glutSpecialUpFunc(SKeysUp);


    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 1;
}