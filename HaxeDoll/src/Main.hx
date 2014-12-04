import ragdoll.PointMass;
import ragdoll.Skeleton;
import ragdoll.ParticleSystem;
import luxe.Input;

class Main extends luxe.Game {

	var timeStep : Float;
	var skeleton : Skeleton;
	var pSystem : ParticleSystem;
	
    override function ready() {
    	timeStep = 1.0 / 30.0;
    	skeleton = new Skeleton();

    	pSystem = new ParticleSystem(1);
    } //ready

    override function onkeyup( e:KeyEvent ) {
        if(e.keycode == Key.escape) {
            Luxe.shutdown();
        }
        if(e.keycode == Key.space) {
	    	pSystem.timeStep();
        }

    } //onkeyup

    override function update(dt:Float) {
    	//skeleton.update(timeStep);
    	//skeleton.render();

	    	pSystem.timeStep();
    	pSystem.render();
    } //update


} //Main
