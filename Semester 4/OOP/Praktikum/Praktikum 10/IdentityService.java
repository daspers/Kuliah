import java.util.*;

public class IdentityService extends AbstractService{
	private final ArrayList<String> identityList= new ArrayList<String>();
	public IdentityService(String a){
		super(a);
	}
	public final ArrayList<String> getIdentity(){
		return identityList;
	}
	public void addIdentity(String a){
		if(super.getServiceState()==STATE.RUNNING){
			identityList.add(a);
		}
	}
	public void removeIdentity(String a){
		if(super.getServiceState()==STATE.RUNNING){
			for(int i=0;i<identityList.size();i++){
				if(identityList.get(i).equals(a)){
					identityList.remove(i);
					return;
				}
			}
		}
	}
	public void init(){
		super.setServiceState(STATE.INIT);
	}
	public void start(){
		super.setServiceState(STATE.RUNNING);
	}
	public void stop(){
		super.setServiceState(STATE.DIE);
	}
	public Boolean isIdentityExist(String a){
		if(super.getServiceState()!=STATE.RUNNING)
			return null;
		for(int i=0;i<identityList.size();i++){
			if(identityList.get(i).equals(a)){
				return true;
			}
		}
		return false;
	}
}
