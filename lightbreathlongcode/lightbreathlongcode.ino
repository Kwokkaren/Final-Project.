// File: LED_linear_levels_if_global.pde
//
// Use PWM to control the brightness of an LED.
// Pattern is a linear ramp up to a constant, followed by a linear decrease
// back to the starting intensity. Repeat indefinitely. Timing is controlled
// by a single loop. Switching between phases is determined with "if" statements
// that check the current (estimate of) time. Timing is still imprecise because the
// use of loop delays ignores time spent executing commands other than delay().
// Timing and ramp parameters are declared as gobal variables so they can be computed
// once at startup. This removes unecessary computation from the loop function.
//
// Gerald Recktenwald, gerry@me.pdx.edu, 20 August 2011
int LED_pin = 11; // must be one of 3, 5, 6, 9, 10 or 11
int Vmin=20, Vmax=220, ncycle, dtwait; // Min & max of ramps, total cycles, loop delay
double ain, bin, aex, bex; // Slopes and intercepts of linear output functions
double dt, dtin, dtpause, dtex, t, t3; // Timing parameters
// -------------
void setup() {
pinMode(LED_pin, OUTPUT); // Initialize pin for output
dt = 0.01; // Time step (seconds). Should be >= 10 milliseconds
dtwait = dt*1000; // Loop delay (milliseconds) corresponding to dt
dtin = 2.0; // Time interval for inhale (seconds)
dtpause = 0.5; // Time interval for pause after inhale (seconds)
dtex = 2.5; // Time intervalfor exhale (seconds)
t3 = dtin + dtpause; // Time at end of the pause (seconds)
ncycle = ( dtin + dtpause + dtex ) / dt; // Total time steps in a cycle
// -- Use other time interval and range parameters to compute slopes and intercepts of v(t)
ain = double(Vmax - Vmin)/dtin; // Slope during inhale
bin = double(Vmin); // Intercept during inhale
aex = double(Vmin - Vmax)/dtex; // Slope during exhale
bex = double(Vmax) - aex*t3; // Intercept during exhale
}
// -------------
void loop() {
int i, v;
double t;
t = 0.0;
for ( i=1; i<=ncycle; i++ ) {
t += dt;
if ( t <= dtin ) {
v = int( ain*t + bin );
} else if ( t <= t3 ) {
v = Vmax;
} else {
v = int( aex*t + bex );
}
analogWrite(LED_pin, v);
delay(dtwait);
}
}
