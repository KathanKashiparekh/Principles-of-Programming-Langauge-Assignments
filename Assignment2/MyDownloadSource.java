public class MyDownloadSource implements Source{
	public Download d;

	public MyDownloadSource(Download d){
		this.d=d;
	}

	public Listener getSource(){
		return d;
	}
}