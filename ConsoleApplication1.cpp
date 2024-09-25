/*************************************************************
 * 1. Name:
 *      Jackson Clarke, Tyler Phillips
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part of this assignment was determining the logic
 *  for a few of the functions, specifically radiansFromDegrees.
 * 5. How long did it take for you to complete the assignment?
 *      1 Hour
 **************************************************************/

#define _USE_MATH_DEFINES // for M_PI

#include <iostream>  // for CIN and COUT
#include <cmath>     // for sin, cos, and M_PI
#include <math.h>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)


/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
 // your function goes here
double computeDistance(double s, double v, double a, double t) {
    return s + v * t + (0.5 * a) * (t * t);
}
 /**************************************************
  * COMPUTE ACCELERATION
  * Find the acceleration given a thrust and mass.
  * This will be done using Newton's second law of motion:
  *     f = m * a
  * INPUT
  *     f : force, in Newtons (kg * m / s^2)
  *     m : mass, in kilograms
  * OUTPUT
  *     a : acceleration, in meters/second^2
  ***************************************************/
double computeAcceleration(double f, double m) {
    return f / m;
}
  /***********************************************
   * COMPUTE VELOCITY
   * Starting with a given velocity, find the new
   * velocity once acceleration is applied. This is
   * called the Kinematics equation. The
   * equation is:
   *     v = v + a t
   * INPUT
   *     v : velocity, in meters/second
   *     a : acceleration, in meters/second^2
   *     t : time, in seconds
   * OUTPUT
   *     v : new velocity, in meters/second
   ***********************************************/
double computeVelocity(double v, double a, double t) {
    return v + (a * t);
}


   /***********************************************
    * COMPUTE VERTICAL COMPONENT
    * Find the vertical component of a velocity or acceleration.
    * The equation is:
    *     cos(a) = y / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     y : the vertical component of the total
    ***********************************************/
double computeVerticalComponent(double a, double total) {
	return total * cos(a);
}

    /***********************************************
     * COMPUTE HORIZONTAL COMPONENT
     * Find the horizontal component of a velocity or acceleration.
     * The equation is:
     *     sin(a) = x / total
     * This can be expressed graphically:
     *      x
     *    +-----
     *    |   /
     *  y |  / total
     *    |a/
     *    |/
     * INPUT
     *     a : angle, in radians
     *     total : total velocity or acceleration
     * OUTPUT
     *     x : the vertical component of the total
     ***********************************************/
double computeHorizontalComponent(double a, double total) {
	return total * sin(a);
}

     /************************************************
      * COMPUTE TOTAL COMPONENT
      * Given the horizontal and vertical components of
      * something (velocity or acceleration), determine
      * the total component. To do this, use the Pythagorean Theorem:
      *    x^2 + y^2 = t^2
      * where:
      *      x
      *    +-----
      *    |   /
      *  y |  / total
      *    | /
      *    |/
      * INPUT
      *    x : horizontal component
      *    y : vertical component
      * OUTPUT
      *    total : total component
      ***********************************************/
double computeTotalComponent(double x, double y) {
	return sqrt(x * x + y * y);
}


/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double radiansFromDegrees(double d) {
	return d * M_PI / 180;
}


   /**************************************************
    * PROMPT
    * A generic function to prompt the user for a double
    * INPUT
    *      message : the message to display to the user
    * OUTPUT
    *      response : the user's response
    ***************************************************/
double prompt(string message) {
    double response = 0.0;
	cout << message;
	cin >> response;
	return response; 
}

   /****************************************************************
    * MAIN
    * Prompt for input, compute new position, and display output
    ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double x = 0.0; //prompt("What is your position (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
	double t = 1.0; // Time in seconds
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust 
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity

	cout << endl;  // Add a new line for formatting

	// Loop through the simulator five times.
    for (int i = 0; i < 10; ++i) {
		// Convert the angle to radians
		aRadians = radiansFromDegrees(aDegrees);

		// Compute the acceleration due to thrust
		accelerationThrust = computeAcceleration(THRUST, WEIGHT);

		// Compute the horizontal and vertical acceleration due to thrust
		ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
		ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);

		// Compute the total horizontal and vertical acceleration
		ddx = ddxThrust;
		ddy = ddyThrust + GRAVITY;

		// Compute the new position
		x = computeDistance(x, dx, ddx, t);
		y = computeDistance(y, dy, ddy, t);

		// Compute the new velocity
		dx = computeVelocity(dx, ddx, t);
		dy = computeVelocity(dy, ddy, t);

		// Compute the total velocity
		v = computeTotalComponent(dx, dy);

		// Output
		cout.setf(ios::fixed | ios::showpoint);
		cout.precision(2);
		cout << i + 1 <<"s - x,y:(" << x << ", " << y << ")m ";
		cout << " dx,dy:(" << dx << ", " << dy << ")m/s ";
		cout << " speed:" << v << "m/s" ;
        cout << " angle:" << aDegrees << " degrees\n";

		// Prompt for a new angle every 5 seconds
		if (i == 4) {
			cout << endl; // Add a new line for formatting
			aDegrees = prompt("What is the new angle of the LM where 0 is up(degrees)? ");
			cout << endl; // Add a new line for formatting
		}
    }

    return 0;
}