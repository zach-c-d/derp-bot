gapcheck(){
	if(frontLineSensor != onLine)
	{
		while(backLineSensor == onLine)
		{
			if(frontLineSensor == onLine){
				return true;
			}
			if(leftIR == onLine){
				leftTurn = true;
			}
			if(rightIR == onLine){
				rightTurn = true;
			}
			if(rightflameSensor == fire){
				flameRight = true;
			}
			if(leftflameSensor == fire){
				flameLeft = true;
			}
			delay(5 mili);
		}
		return false;
	}
}
			
