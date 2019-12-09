gapcheck(){
	if(frontLineTrack != onLine)
	{
		while(backLineTrack == onLine)
		{
			if(frontLineTrack == onLine){
				return true;
			}
			if(leftIR == onLine){
				leftTurn = true;
			}
			if(rightIR == onLine){
				rightTurn = true;
			}
			delay(10 milli);
		}
		return false;
	}
}
			
