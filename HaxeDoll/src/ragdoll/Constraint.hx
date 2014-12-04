package ragdoll;
import ragdoll.RenderUtil;
import ragdoll.PointMass;
import luxe.Vector;
import luxe.Color;

enum ConstraintType {
	Rigid;
	MinMax;
}

class Constraint {

	public var type : ConstraintType;
	public var point1 : PointMass;
	public var point2 : PointMass;
	public var minLength : Float;
	public var maxLength : Float;

	public function new(_point1 : PointMass, _point2 : PointMass/*, _minLength : Float, _maxLenght : Float, _type : ConstraintType*/) {
		point1 = _point1;
		point2 = _point2;
		/*minLength = _minLength;
		maxLength = _maxLenght;
		type = _type;*/
	}

	public function apply() {
		if(type == Rigid) {

		} else if(type == MinMax) {

		}
	}

	public function render() {
		var x1 = point1.position.x;
		var y1 = point1.position.y;
		var x2 = point2.position.x;
		var y2 = point2.position.y;

		RenderUtil.drawLine(x1, y1, x2, y2, new Color(1.0, 1.0, 1.0, 1.0));
	}
}