package ragdoll;
import luxe.Color;
import luxe.Vector;
import ragdoll.Constraint;
import ragdoll.RenderUtil;
import ragdoll.PointMass;

class Skeleton {
	var Constraints : Array<Constraint>;
	var Points : Array<PointMass>;
	var Forces : Map<PointMass, Vector>;

	public var Gravity : Vector;

	public function new() {
		Gravity = new Vector(0.0, 9.82);
		initHumanSkeleton();
	}

	public function update(timeStep:Float) {
		accumulateForces();
		verletIntegration(timeStep);
		applyConstraints();
	}

	function verletIntegration(timeStep:Float) {
		for(point in Points) {
			point.verlet(timeStep);
		}
	}

	function accumulateForces() {
		for(point in Points) {
			point.accumulateForce(Gravity);
		}
	}

	function applyConstraints() {
		for(constraint in Constraints) {
			/*if(constraint.type == Linear) {
				applyLinearConstraints();
			} else if(constraint.type == Rotation) {
				applyRotationConstraints();
			}*/
		}
	}

	function applyLinearConstraints() {

	}

	function applyRotationConstraints() {

	}

	public function render() {
		for(point in Points) {
			point.render();
		}

		for(constraint in Constraints) {
			constraint.render();
		}
	}

	public function initHumanSkeleton() {
		Points = new Array<PointMass>();
		Constraints = new Array<Constraint>();
		

		var neckLength = 40;
		Points.push(new PointMass(320, 180, 20));
		Points.push(new PointMass(320, 180 + neckLength, 20));
		Constraints.push(new Constraint(Points[0], Points[1]));

		var shoulderWidth = 40;
		var shoulderYPos = neckLength + 20;
		Points.push(new PointMass(320 - shoulderWidth, 180 + shoulderYPos, 20));
		Points.push(new PointMass(320 + shoulderWidth, 180 + shoulderYPos, 20));
		Constraints.push(new Constraint(Points[1], Points[2]));
		Constraints.push(new Constraint(Points[1], Points[3]));

		var ribbcageSize = shoulderYPos + 70;
		Points.push(new PointMass(320, ribbcageSize + 180, 20));
		Constraints.push(new Constraint(Points[1], Points[4]));
		Constraints.push(new Constraint(Points[2], Points[4]));
		Constraints.push(new Constraint(Points[3], Points[4]));

		var upperArmLen = shoulderYPos + 80;
		Points.push(new PointMass(320 - shoulderWidth, 180 + upperArmLen, 20));
		Points.push(new PointMass(320 + shoulderWidth, 180 + upperArmLen, 20));
		Constraints.push(new Constraint(Points[2], Points[5]));
		Constraints.push(new Constraint(Points[3], Points[6]));

		var lowerArmLen = upperArmLen + 80;
		Points.push(new PointMass(320 - shoulderWidth, 180 + lowerArmLen, 20));
		Points.push(new PointMass(320 + shoulderWidth, 180 + lowerArmLen, 20));
		Constraints.push(new Constraint(Points[5], Points[7]));
		Constraints.push(new Constraint(Points[6], Points[8]));

		var lowerBack = ribbcageSize + 1;
		Points.push(new PointMass(320, 180 + lowerBack, 20));
		Constraints.push(new Constraint(Points[4], Points[9]));

		var upperLegs = lowerBack + 30;
		var legSeparation = 30;
		Points.push(new PointMass(320 - legSeparation, 180 + upperLegs, 20));
		Points.push(new PointMass(320 + legSeparation, 180 + upperLegs, 20));
		Constraints.push(new Constraint(Points[9], Points[10]));
		Constraints.push(new Constraint(Points[9], Points[11]));
		Constraints.push(new Constraint(Points[10], Points[11]));

		var knee = upperLegs + 80;
		Points.push(new PointMass(320 - legSeparation, 180 + knee, 20));
		Points.push(new PointMass(320 + legSeparation, 180 + knee, 20));
		Constraints.push(new Constraint(Points[10], Points[12]));
		Constraints.push(new Constraint(Points[11], Points[13]));

		var lowerLegs = knee + 80;
		Points.push(new PointMass(320 - legSeparation, 180 + lowerLegs, 20));
		Points.push(new PointMass(320 + legSeparation, 180 + lowerLegs, 20));
		Constraints.push(new Constraint(Points[12], Points[14]));
		Constraints.push(new Constraint(Points[13], Points[15]));
	}
}