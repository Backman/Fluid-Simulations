package ragdoll;
import luxe.Color;
import luxe.Vector;

class RenderUtil {
	public static function drawPoint(_x : Float, _y : Float, _color : Color, _radius : Float) {
		Luxe.draw.circle({
			immediate : true,
			x : _x, y : _y,
			r : _radius,
			color : _color
			});
	}

	public static function drawLine(_x1 : Float, _y1 : Float, _x2 : Float, _y2 : Float, _color : Color) {
		Luxe.draw.line({
			immediate : true,
			p0 : new Vector(_x1, _y1),
			p1 : new Vector(_x2, _y2),
			color : _color
			});
	}
}