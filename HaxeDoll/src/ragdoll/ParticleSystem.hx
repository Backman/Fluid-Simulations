package ragdoll;
import ragdoll.RenderUtil;
import luxe.Vector;
import luxe.Color;

class ParticleSystem {
	var _x : Array<Vector>;
	var _oldX : Array<Vector>;
	var _a : Array<Vector>;
	var _gravity : Vector;
	var _timeStep : Float;
	var _numParticles : Int;

	public function new(numParticles:Int) {
		_numParticles = numParticles;
		_x = new Array<Vector>();
		_oldX = new Array<Vector>();
		_a = new Array<Vector>();
		for(i in 0...numParticles) {
			_x[i] = new Vector(10.0, 0);
			_oldX[i] = new Vector();
			_a[i] = new Vector();
		}

		_gravity = new Vector(0.0, 1.0);
		_timeStep = 1.0 / 10.0;
	}

	public function timeStep() {
		accumulateForces();
		verlet();
		applyConstraints();
	}

	private function verlet() {
		for(i in 0..._numParticles) {
			var temp = _x[i].clone();

			var newX = new Vector();
			newX.add(_x[i]);
			newX.subtract(_oldX[i]);
			newX.add(_a[i]);
			newX.multiplyScalar(_timeStep * _timeStep);

			_x[i].add(newX);

			_oldX[i] = temp;
		}
	}

	private function accumulateForces() {
		for(i in 0..._numParticles) {
			_a[i] = _gravity;
		}
	}

	private function applyConstraints() {

	}

	public function render() {
		for(i in 0..._numParticles) {
			RenderUtil.drawPoint(_x[i].x, _x[i].y, new Color(1.0, 0.0, 0.0, 1.0), 5.0);
		}
	}
}