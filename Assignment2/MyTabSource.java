public class MyTabSource implements Source{
	public Tab t;

	public MyTabSource(Tab t){
		this.t=t;
	}

	public Listener getSource(){
		return t;
	}
}