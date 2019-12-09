gapcheck(){
	if(FLLineSensor != onLine && FRLineSensor != onLine && FMLineSensor != onLine && (BLLineSensor == onLine || BRLineSensor == onLine || BMLineSensor == onLine))
	{
		frontSensorOff = true;
	}else if((FLLineSensor == onLine || FRLineSensor == onLine ||  FMLineSensor == onLine) && (BLLineSensor == onLine || BRLineSensor == onLine || BMLineSensor == onLine) && frontSensorOff){
		frontSensorOff = false;
		return true;
	}else{
		return false;
	}
}

fireCheck(){
	if(rightflameSensor == fire){
		flameRight = true;
	}
	if(leftflameSensor == fire){
		flameLeft = true;
	}
}

cornerCheck(){
	if(leftIR == onLine){
		leftTurn = true;
	}
	if(rightIR == onLine){
		rightTurn = true;
	}
}
			
