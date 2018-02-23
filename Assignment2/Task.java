public class Task implements Runnable{
	private int size;
	private Source mySource;

	public Task(int size,Source mySource){
		this.size=size;
		this.mySource=mySource;
	}


	@Override
	public void run(){
		try{
			Thread.sleep(size);
		} catch(InterruptedException e){
			e.printStackTrace();
		}
		mySource.getSource().onEvent(size);
	}
}