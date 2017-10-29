#include <time.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/freeglut.h>
#include <string>
#include <queue>

#define range 500
#define frame 100
#define DELAY 10

using namespace std;

const GLfloat pi = acos(-1);
const GLfloat tr = 2.0/frame;

int r,n=1;
string s, t;
bool mode2d = true, baca = true, proses = false;
queue<string> input;
GLfloat *vertex, *tvertex, x, y, z, k, dx, dy, dz, dk, d, A=1.0f;
GLfloat matrix[3][3] = {0,0,0, 0,0,0, 0,0,0};

void delay(int d)
{
    long a = clock() + d;
    while(clock()<a);
}

void display2d(){
    int i;
    GLfloat x,y;
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //Cartesian line
    glBegin(GL_LINES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);
        for(i=0, x=0.0f; i<50;i++){
            x += 0.02f;
            glVertex3f(x, 0.01f, 0.0f);
            glVertex3f(x, -0.01f, 0.0f);
            
        }
        for(i=0, x=0.0f; i<50;i++){
            x -= 0.02f;
            glVertex3f(x, 0.01f, 0.0f);
            glVertex3f(x, -0.01f, 0.0f);
            
        }
        for(i=0, y=0.0f; i<50;i++){
            y += 0.02f;
            glVertex3f(0.01f, y, 0.0f);
            glVertex3f(-0.01f, y, 0.0f);
            
        }
        for(i=0, y=0.0f; i<50;i++){
            y -= 0.02f;
            glVertex3f(0.01f, y, 0.0f);
            glVertex3f(-0.01f, y, 0.0f);
            
        }
    glEnd();
    
    //Polygon
    glColor4f(1.0f, 0.0f, 0.0f, A);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, tvertex);
    glDrawArrays(GL_POLYGON, 0, n);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glFlush();
}

void setmatrix(GLfloat x){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            matrix[i][j] = x;
        }
    }
}

void matrixmult(){
    GLfloat t1, t2, t3;
    for(int i=0;i<n;i++){
        t1 = tvertex[3*i];
        t2 = tvertex[3*i+1];
        t3 = tvertex[3*i+2];
        tvertex[3*i] = t1*matrix[0][0] + t2*matrix[0][1] + t3*matrix[0][2];
        tvertex[3*i+1] = t1*matrix[1][0] + t2*matrix[1][1] + t3*matrix[1][2];
        tvertex[3*i+2] = t1*matrix[2][0] + t2*matrix[2][1] + t3*matrix[2][2];
    }
}

void reflect(GLfloat x, GLfloat y, GLfloat z){
    matrixmult();
    for(int i=0;i<n;i++){
        tvertex[3*i] +=x;
        tvertex[3*i+1] +=y;
        tvertex[3*i+2] +=z;
    }
}

void translate(GLfloat X, GLfloat Y, GLfloat Z){
    int i;
    for(i=0;i<n;i++){
        tvertex[3*i] +=X;
        tvertex[3*i+1] +=Y;
        tvertex[3*i+2] +=Z;
    }
}

void dilate(GLfloat k){
    int i;
    setmatrix(0);
    for(i=0;i<3;i++){
        matrix[i][i] = k;
    }
    matrixmult();
}

void rotate(GLfloat d, GLfloat x, GLfloat y, GLfloat z){
    d = pi*d / 180;
    if(mode2d){
        setmatrix(0);
        matrix[0][0] = cos(d);
        matrix[0][1] = -sin(d);
        matrix[1][0] = sin(d);
        matrix[1][1] = cos(d);
    }
    else{
        matrix[0][0] = cos(d)*cos(d);
        matrix[0][1] = (sin(d)-1)*sin(d)*cos(d);
        matrix[0][2] = sin(d)*(cos(d)*cos(d)+sin(d));
        matrix[1][0] = sin(d)*cos(d);
        matrix[1][1] = pow(sin(d),3)+pow(cos(d),2);
        matrix[1][2] = (sin(d)-1)*sin(d)*cos(d);
        matrix[2][0] = -sin(d);
        matrix[2][1] = sin(d)*cos(d);
        matrix[2][2] = cos(d)*cos(d);
    }
    translate(-x, -y, -z);
    matrixmult();
    translate(x, y, z);
}

void shear(string t, GLfloat k){
    if(t == "x"){
        matrix[0][1] = k; // 
        matrix[0][2] = k; //
    }
    else if(t == "y"){
        matrix[1][0] = k; //
        matrix[1][2] = k; //
    }
    else{
        matrix[2][0] = k; //
        matrix[2][1] = k; //
    }
    matrixmult();
}

void stretch(string t, GLfloat k){
    if(t == "x")
        matrix[0][0] = k;
    else if(t == "y")
        matrix[1][1] = k;
    else if(t == "z")
        matrix[2][2] = k;
    matrixmult();
}

void reset(){
    int i;
    for(i=0;i<n;i++){
        tvertex[3*i] = vertex[3*i];
        tvertex[3*i+1] = vertex[3*i+1];
        tvertex[3*i+2] = vertex[3*i+2];
    }
}

void readvertex(){
    GLfloat x, y;
    cin>>n;
    vertex = (GLfloat*) malloc(n*3*sizeof(GLfloat));
    tvertex = (GLfloat*) malloc(n*3*sizeof(GLfloat));
    for(int i=0;i<n;i++){
        cin>>x>>y;
        vertex[3*i] = x/range;
        vertex[3*i+1] = y/range;
        vertex[3*i+2] = 0;
    }
    reset();
}

void showhelp(){
    cout<<"---------------------------------------------Daftar perintah-----------------------------------------------------------\n";
    cout<<"2 dimensi\n";
    cout<<" new <n>\n";
    cout<<"    <x1> <y1>\n";
    cout<<"    Membuat sebuah poligon dengan n titik sudut, diikuti masukan titik <x1> <y1>\n";
    cout<<" translate <x1> <y1>\n";
    cout<<"    Mentranslasikan poligon ke arah sumbu x sebesar x1, dan ke arah sumbu y sebesar y1\n";
    cout<<" dilate <k>\n";
    cout<<"    Mendilatasikan poligon dengan skala k\n";
    cout<<" rotate <d> <x1> <y1>\n";
    cout<<"    Merotasikan poligon sebesar d derajat, dengan titik sumbu x1,y1\n";
    cout<<" reflect <param>\n";
    cout<<"    param bernilai y=x, y=-x, x, y atau (x1,y2)\n";
    cout<<"    Mencerminkan poligon terhadap param\n";
    cout<<" shear <param> <k>\n";
    cout<<"    param bernilai x atau y dan k bernilai real\n";
    cout<<"    Menggeser poligon sejajar sumbu param dengan faktor k\n";
    cout<<" stretch <param> <k>\n";
    cout<<"    param bernilai x atau y dan k bernilai real untuk 2 dimensi\n";
    cout<<"    Medilatasikan poligon sejajar sumbu param dengan faktor k\n";
    cout<<" custom <m1> <m2> <m3> <m4>\n";
    cout<<"    Mentransformasikan poligon matriks transformasi berelemen(m1, m2, m3, m4)\n";
    cout<<"--\n";
    cout<<"3 dimensi\n";
    cout<<" new <n>\n";
    cout<<"    <x1> <y1> <z1>\n";
    cout<<"    Membuat sebuah poligon dengan n titik sudut, diikuti masukan titik <x1> <y1> <z1>\n";
    cout<<" translate <x1> <y1> <z1>\t\n";
    cout<<"    Mentranslasikan poligon ke arah sumbu x sebesar x1, ke arah sumbu y sebesar y1, dan ke arah sumbu z sebesar z1\n";
    cout<<" dilate <k>\n";
    cout<<"    Mendilatasikan poligon dengan skala k\n";
    cout<<" rotate <d> <x1> <y1> <z1>\n";
    cout<<"    Merotasikan poligon sebesar d derajat, dengan titik sumbu x1,y1,z1\n";
    cout<<" reflect <param>\n";
    cout<<"    param bernilai y=x, y=-x, y=z, y=-z, x=z, x=-z, xz, xy, yz atau (x1,y1,z1)\n";
    cout<<"    Mencerminkan poligon terhadap param\n";
    cout<<" shear <param> <k>\n";
    cout<<"    param bernilai x atau y atau z dan k bernilai real\n";
    cout<<"    Menggeser poligon sejajar sumbu param dengan faktor k\n";
    cout<<" stretch <param> <k>\n";
    cout<<"    param bernilai x atau y atau z dan k bernilai real\n";
    cout<<"    Medilatasikan poligon sejajar sumbu param dengan faktor k\n";
    cout<<" custom <m1> <m2> <m3> <m4> <m5> <m6> <m7> <m8> <m9>\n";
    cout<<"    Mentransformasikan poligon matriks transformasi berelemen(m1, m2, m3, m4, m5, m6, m7, m8, m9)\n";
    cout<<"--\n";
    cout<<" reset\n";
    cout<<"    Menampilkan posisi awal poligon\n";
    cout<<" multiple <n>\n";
    cout<<"    Melakukan transformasi linier(pada daftar perintah selain multiple, help, reset, exit) terhadap poligon sebanyak n\n";
    cout<<" help\n";
    cout<<"    Menampilkan daftar perintah\n";
    cout<<" exit\n";
    cout<<"    Keluar dari program\n";
    cout<<"-----------------------------------------------------------------------------------------------------------------------\n";
}

void printvertex(){
    for(int i=0;i<n;i++){
        cout<<"("<<tvertex[3*i]<<","<<tvertex[3*i+1]<<","<<tvertex[3*i+2]<<")"<<endl;
    }
}

void StoP(string t){
    int i;
    string temp="";
    for(i=1;t[i]!=','; i++){
        temp +=t[i];
    }
    x = stof(temp)/500;
    temp="";
    while(t[i]!=','||t[i]!=')'){
        temp +=t[i];
        i++;
    }
    y = stof(temp)/500;
    if(!mode2d){
        temp="";
        while(t[i]!=')'){
            temp += t[i];
            i++;
        }
        z = stof(temp)/500;
    }
    else
        z = 0;
}

void readinput(){
    string b;
    int i,j,m,a;
    if(baca){
        baca = false;
        cin>>s;
        if(s == "new"){
            readvertex();
			glutPostRedisplay();
            baca = true;
        }
        else if(s == "translate"){
            input.push(s);
            j = (mode2d? 2:3);
            for(i=0;i<j;i++){
                cin>>b;
                input.push(b);
            }
        }
        else if(s == "dilate"){
            input.push(s);
            cin>>b;
            input.push(b);
        }
        else if(s == "rotate"){
            input.push(s);
            j = mode2d?3:4;
            for(i=0;i<j;i++){
                cin>>b;
                input.push(b);
            }
        }
        else if(s == "reflect"){
            input.push(s);
            cin>>b;
            input.push(b);
        }
        else if(s == "shear"){
            input.push(s);
            for(i=0;i<2;i++){
                cin>>b;
                input.push(b);
            }
        }
        else if(s == "stretch"){
            input.push(s);
            for(i=0;i<2;i++){
                cin>>b;
                input.push(b);
            }
        }
        else if(s == "custom"){
            input.push(s);
            j = mode2d?4:9;
            for(i=0;i<j;i++){
                cin>>b;
                input.push(b);
            }
        }
        else if(s == "multiple"){
            cin >> m;
            for(i=0;i<m;i++){
                cin>>s;
                if(s == "translate"){
                    input.push(s);
                    a = mode2d?2:3;
                    for(j=0;j<a;j++){
                        cin>>b;
                        input.push(b);
                    }
                }
                else if(s == "dilate"){
                    input.push(s);
                    cin>>b;
                    input.push(b);
                }
                else if(s == "rotate"){
                    input.push(s);
                    a = mode2d?3:4;
                    for(j=0;j<a;j++){
                        cin>>b;
                        input.push(b);
                    }
                }
                else if(s == "reflect"){
                    input.push(s);
                    cin>>b;
                    input.push(b);
                }
                else if(s == "shear"){
                    input.push(s);
                    for(j=0;j<2;j++){
                        cin>>b;
                        input.push(b);
                    }
                }
                else if(s == "stretch"){
                    input.push(s);
                    for(j=0;j<2;j++){
                        cin>>b;
                        input.push(b);
                    }
                }
                else if(s == "custom"){
                    input.push(s);
                    a = mode2d?4:9;
                    for(j=0;j<a;j++){
                        cin>>b;
                        input.push(b);
                    }
                }
                else{
                    cout<<"Wrong Input!!\n";
                    i--;
                }
            }
        }
        else if(s == "reset"){
            input.push(s);
        }
        else if(s=="exit"){
            glutLeaveMainLoop();
            baca = true;
        }
        else if(s=="help"){
            showhelp();
            baca = true;
        }
        else{    
            cout<<"Wrong Input!!\n";
            baca = true;
        }
    }
    else{
        if(!proses && input.empty())
            baca = true;
        else if(!proses){
            glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            r=0;
            s = input.front();
            input.pop();
            if(s == "translate"){   
                x = stof(input.front())/range;
                input.pop();
                y = stof(input.front())/range;
                input.pop();
                if(mode2d)
                    z = 0;
                else{
                    z = stof(input.front())/range;
                    input.pop();
                }
            }
            else if(s == "dilate"){
                k = stof(input.front());
                input.pop();
            }
            else if(s == "rotate"){
                d = stof(input.front());
                input.pop();
                x = stof(input.front())/range;
                input.pop();
                y = stof(input.front())/range;
                input.pop();
                if(mode2d)
                    z = 0;
                else{
                    z = stof(input.front())/range;
                    input.pop();
                }
            }
            else if(s == "reflect"){
                // pake matrix
                t = input.front();
                input.pop();
                setmatrix(0);
                x = y = z = 0;
                if(t == "x" || t == "xz" || t == "zy"){
                    matrix[0][0] = 1;
                    matrix[1][1] = -1;
                    matrix[2][2] = 1;
                }
                else if( t == "y" || t == "yz"  || t == "zy"){
                    matrix[0][0] = -1;
                    matrix[1][1] = 1;
                    matrix[2][2] = 1;
                }
                else if(t == "xy" || t == "yx"){
                    matrix[0][0] = 1;
                    matrix[1][1] = 1;
                    matrix[2][2] = -1;
                }
                else if(t == "y=x" || t == "x=y"){
                    matrix[0][1] = 1;
                    matrix[1][0] = 1;
                    matrix[2][2] = 1;
                }
                else if(t == "y=-x" || t == "x=-y"){
                    matrix[0][1] = -1;
                    matrix[1][0] = -1;
                    matrix[2][2] = 1;
                }
                else if(t == "y=z" || t == "z=y"){
                    matrix[0][0] = 1;
                    matrix[1][2] = 1;
                    matrix[2][1] = 1;
                }
                else if(t == "y=-z" || t == "z=-y"){
                    matrix[0][0] = 1;
                    matrix[1][2] = -1;
                    matrix[2][1] = -1;
                }
                else if(t == "x=z" || t == "z=x"){
                    matrix[0][2] = 1;
                    matrix[1][1] = 1;
                    matrix[2][0] = 1;
                }
                else if(t == "x=-z" || t == "z=-x"){
                    matrix[0][2] = -1;
                    matrix[1][1] = 1;
                    matrix[2][0] = -1;
                }
                else{
                    StoP(t);
                    matrix[0][0] = -1;
                    matrix[1][1] = -1;
                    matrix[2][2] = -1;
                    x*=2;
                    y*=2;
                    z*=2;
                }
            }
            else if(s == "shear"){
                t = input.front();
                input.pop();
                k = stof(input.front());
                input.pop();
                setmatrix(0);
                matrix[0][0] = 1;
                matrix[1][1] = 1;
                matrix[2][2] = 1;
            }
            else if(s == "stretch"){
                t = input.front();
                input.pop();
                k = stof(input.front());
                input.pop();
                setmatrix(0);
                matrix[0][0] = 1;
                matrix[1][1] = 1;
                matrix[2][2] = 1;
            }
            else if(s == "custom"){
                a = mode2d? 2 : 3;
                setmatrix(0);
                for(i=0;i<a;i++){
                    for(j=0;j<a;j++){
                        matrix[i][j] = stof(input.front());
                        input.pop();
                    }
                }
            }
            proses = true;
        }
        else{
            if(s == "translate"){
                // pake x y z
                dx = x/frame;
                dy = y/frame;
                dz = z/frame;
                if(r<frame)
                {                       
                    translate(dx, dy, dz);
                    r++;
                }
                else
                {
                    proses = false;
                }
            }
            else if(s == "dilate"){
                // pake k
                dk = pow(k,1.0/frame);
                if(r<frame)
                {
                    dilate(dk);  
                    r++;              
                }
                else
                {
                    proses = false;
                }
            }
            else if(s == "rotate"){
                // pake d x y z
                if(d-r>=1)
                {
                    rotate(1, x, y, z);
                    r++;
                }
                else if(r-d>=1){
                    rotate(-1, x, y, z);
                    r--;
                }
                else
                {
                    rotate(d-r, x, y, z);
                    proses = false;
                }
            }
            else if(s == "reflect"){
                // pake matrix
                if(r<=frame)
                {
                    if(r<frame/2)
                    {
                        r++;
                        A-=tr;
                    }
                    else if(r==frame/2)
                    {
                        reflect(x, y, z);
                        r++;
                    }
                    else if(r<=frame && r>frame/2)
                    {
                        A+=tr;
                        r++;
                    }
                }
                else
                {
                    proses=false;
                }
            }
            else if(s == "shear"){
                // pake matrix
                dk = k/frame;
                if(r<frame)
                {
                    shear(t, dk);
                    r++;
                }
                else
                {
                    proses = false;
                }

                
            }
            else if(s == "stretch"){
                // pake matrix
                dk = pow(k,1.0/frame);
                if(r<frame)
                {
                    stretch(t, dk);  
                    r++;              
                }
                else
                {
                    proses = false;
                }

            }
            else if(s == "custom"){
                // pake matrix
                if(r<=frame)
                {
                    if(r<frame/2)
                    {
                        r++;
                        A-=tr;
                    }
                    else if(r==frame/2)
                    {
                        matrixmult();
                        r++;
                    }
                    else if(r<=frame && r>frame/2)
                    {
                        A+=tr;
                        r++;
                    }
                }
                else
                {
                    proses=false;
                }
            }
            else if(s == "reset")
            {
                if(r<=frame)
                {
                    if(r<frame/2)
                    {
                        r++;
                        A-=tr;
                    }
                    else if(r==frame/2)
                    {
                        reset();
                        r++;
                    }
                    else if(r<=frame && r>frame/2)
                    {
                        A+=tr;
                        r++;
                    }
                }
                else
                {
                    proses=false;
                }
            }
            glutPostRedisplay();
            delay(DELAY);
        }
    }
}

int main(int argc, char** argv){
    tvertex = (GLfloat*) malloc(3*sizeof(GLfloat));
    tvertex[0] = 0.0f;
    tvertex[1] = 0.0f;
    tvertex[2] = 0.0f;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("ALGEO");
    glutDisplayFunc(display2d);
    glutIdleFunc(readinput);
    glutMainLoop();
    free(vertex);
    free(tvertex);
    return 0;
}
