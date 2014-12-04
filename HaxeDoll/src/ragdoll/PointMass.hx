package ragdoll;
import luxe.Vector;
import luxe.Color;
import ragdoll.RenderUtil;

class PointMass {
	/** Current position */
	public var position : Vector;
	/** Previous position */
	public var oldPosition : Vector;
	/** Force accumulation */
	public var a : Vector;
	/** Mass */
	public var mass : Float;
	/** 1.0 / Mass */
	public var invMass : Float;

	/** Constructor */
	public function new(_x : Float, _y : Float, _mass : Float) {
		position = new Vector(_x, _y);
		oldPosition = position.clone();
		setMass(_mass);
	}

	/** Verlet integration */
	public function verlet(timeStep:Float) {
		var temp = position.clone();

		var newPos = new Vector(position.x, position.y);
		newPos.subtract(oldPosition);
		newPos.add(a);
		newPos.multiplyScalar(timeStep * timeStep);

		position.add(newPos);

		oldPosition = temp;
	}

	public function accumulateForce(force:Vector) {
		a = force;//Vector.Multiply(force, mass);
	}

	/** Render function */
	public function render() {
		RenderUtil.drawPoint(position.x, position.y, new Color(0.8, 0.3, 0.4, 1.0), 5);
	}

	/** Set a new mass to the point */
	public function setMass(newMass:Float) {
		mass = newMass;

		if(mass != 0.0) {
			invMass = 1.0 / mass;
		} else {
			invMass = 99999999.0;
		}
	}
}