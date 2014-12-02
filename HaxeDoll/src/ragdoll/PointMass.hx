package ragdoll;
import luxe.Vector;
import luxe.Color;
import ragdoll.RenderUtil;

class PointMass {
	public var x : Float;
	public var y : Float;
	public var mass : Float;
	public var invMass : Float;

	public function new(_x : Float, _y : Float, _mass : Float) {
		x = _x;
		y = _y;
		mass = _mass;

		if(mass != 0.0) {
			invMass = 1.0 / mass;
		} else {
			invMass = 99999999.0;
		}
	}

	public function update(delta : Float) {
		RenderUtil.drawPoint(x, y, new Color(0.8, 0.3, 0.4, 1.0), 5);
	}

	public function setMass(newMass:Float) {
		mass = newMass;

		if(mass != 0.0) {
			invMass = 1.0 / mass;
		} else {
			invMass = 99999999.0;
		}
	}

	public function getPosition() : Vector {
		return new Vector(x, y);
	}
}