//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute in modified or unmodified form! 
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "cube_system_split.h"


// Render the scene
void cube_system_split::render()
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	// Calculate the aspect ratio for use in glOrtho
	double aspect = width/static_cast<double>(height);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Save the current view port
	glPushAttrib(GL_VIEWPORT_BIT);

	// Clear the screen
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/********
	Additional Task: Render the cube system in 4 small screens. Three of them
	                 shall be orthographic projections of the main layers while
					 the fourth is a perspective projection. Take care that
					 no content from one window renders above its area. The
					 width and height of the window is stored in the variables
					 "width" and "height". Do not remove any code from this method.
	Zusatzaufgabe:   Rendern Sie das Wuerfelsystem in 4 kleinen Bildschirmen.
	                 Drei von ihnen sollen orthographische Projektionen der Haupt-
					 eben und eine soll eine perspektivische Projektion sein. 
					 Achten Sie darauf, dass der Inhalt der Fenster nicht ueber seinen
					 Bereich hinausrendert. Die Hoehe und Breite des Gesamtfensters
					 ist in den Variablen "width" und "height" gespeichert. Entfernen
					 Sie keinen Code aus dieser Methode.
     ***********/

	int halfWidth = width / 2;
	int halfHeight = height / 2;

	// xy
	glViewport(0, halfHeight, halfWidth, halfHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect * 5, aspect * 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	render_system();

	// yz
	glViewport(halfWidth, halfHeight, halfWidth, halfHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect * 5, aspect * 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 0, 1, 0); // Rotate to look along the YZ plane
	render_system();

	// xz
	glViewport(0, 0, halfWidth, halfHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-aspect * 5, aspect * 5, -5, 5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0); // Rotate to look along the XZ plane
	render_system();

	// perspective
	glViewport(halfWidth, 0, halfWidth, halfHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, aspect, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	render_system();

	// Restore the old view port
	glPopAttrib();

	// Render split screen lines to span the whole window.
	// For this the projection matrix and modelview matrix is
	// set to the identity matrix. This ensures that the window
	// area always ranges from -1 to 1 in X and Y. The Z-direction
	// is omitted.
	// After that a cross is rendered
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Do not perform depth testing
	glDisable(GL_DEPTH_TEST);

	// Render a cross in gray
	glColor3d(0.5, 0.5, 0.5);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2d(0, -1);
	glVertex2d(0, 1);
	glVertex2d(-1, 0);
	glVertex2d(1, 0);
	glEnd();

}



// Set debug text
void cube_system_split::set_text(std::stringstream &stream)
{
	stream<<"Cube system (top left: XY, top right: YZ, bottom left: XZ, bottom right: perspective)";
}