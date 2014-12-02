import ragdoll.PointMass;
import ragdoll.Skeleton;
import luxe.Input;

class Main extends luxe.Game {

	var skeleton : Skeleton;
	
    override function ready() {
    	skeleton = new Skeleton();
    } //ready

    override function onkeyup( e:KeyEvent ) {

        if(e.keycode == Key.escape) {
            Luxe.shutdown();
        }

    } //onkeyup

    override function update(dt:Float) {
    	skeleton.update(dt);
    } //update


} //Main
