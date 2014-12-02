package ragdoll;
import ragdoll.RenderUtil;
import ragdoll.PointMass;
import luxe.Vector;
import luxe.Color;

class Constraint {
	public var point1 : PointMass;
	public var point2 : PointMass;

	public function new(p1 : PointMass, p2 : PointMass) {
		point1 = p1;
		point2 = p2;
	}

	public function render() {
		RenderUtil.drawLine(point1.x, point1.y, point2.x, point2.y, new Color(1.0, 1.0, 1.0, 1.0));
	}
}