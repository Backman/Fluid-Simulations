import ragdoll.PointMass;
import ragdoll.Skeleton;
import luxe.Input;

class Main extends luxe.Game {

	var updateRate : Float;
	var skeleton : Skeleton;
	
    override function ready() {
    	updateRate = 1.0 / 60.0;
    	skeleton = new Skeleton();
    } //ready

    override function onkeyup( e:KeyEvent ) {

        if(e.keycode == Key.escape) {
            Luxe.shutdown();
        }

    } //onkeyup

    override function update(dt:Float) {
    	skeleton.update(updateRate);
    	skeleton.render();
    } //update


} //Main
