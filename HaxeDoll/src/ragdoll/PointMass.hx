package ragdoll;
import luxe.Vector;

class PointMass {
	var position : Vector;
	var x : Float;
	var y : Float;
	var mass : Float;
	var invMass : Float;

	public function new(_position : Vector, _mass : Float) {
		position = _position;
		mass = _mass;

		if(mass != 0.0) {
			invMass = 1.0 / mass;
		} else {
			invMass = 99999999.0;
		}
	}

	public function new(_x : Float, _y : Float, _mass : Float) {
		position = new Vector(x, y);
		mass = _mass;

		if(mass != 0.0) {
			invMass = 1.0 / mass;
		} else {
			invMass = 99999999.0;
		}
	}
}