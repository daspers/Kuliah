import java.util.*;

public class CompositeService extends AbstractService{
	private ArrayList<AbstractService> serviceList= new ArrayList<AbstractService>();
	public CompositeService(String a){
		super(a);
	}
	public ArrayList<AbstractService> getServices(){
		return serviceList;
	}
	public void addService(AbstractService a){
		if(super.getServiceState() != STATE.DIE){
			serviceList.add(a);
		}
	}
	public void removeService(AbstractService a){
		if(super.getServiceState() != STATE.DIE){
			for(int i=0;i<serviceList.size();i++){
				if(a.toString() == serviceList.get(i).toString()){
					serviceList.remove(i);
					return;
				}
			}
		}
	}
	public void init(){
		super.setServiceState(STATE.INIT);
		for(int i=0;i<serviceList.size();i++){
			serviceList.get(i).setServiceState(STATE.INIT);
		}
	}
	public void start(){
		super.setServiceState(STATE.RUNNING);
		for(int i=0;i<serviceList.size();i++){
			serviceList.get(i).setServiceState(STATE.RUNNING);
		}
	}
	public void stop(){
		super.setServiceState(STATE.DIE);
		int c=0;
		for(int i=0;i<serviceList.size();i++){
			if(serviceList.get(i).getServiceState() == STATE.RUNNING)
				c++;
			serviceList.get(i).setServiceState(STATE.DIE);
		}
		System.out.println("RUNNING service total : " + c);
	}
}
