
function UniEAP(){
    this.WEB_APP_NAME  = "";
    this.FORM_NAME     = "EAPForm";
    this.DEBUG         = false;
    this.orderbyDB  = true;
    if(this.WEB_APP_NAME!="")
        this.WEB_APP_NAME="/"+this.WEB_APP_NAME;
    this.DW_OPEN_WIN_URL        =this.WEB_APP_NAME + "/DataWindowPopWinAction.do"; 
    this.DW_QUERY_WIN_URL       =this.WEB_APP_NAME + "/DataWindowQueryWinAction.do";  
    this.resultSplit = "RESPONSE_SEPARATOR";
    this.bitsOfOneChinese = 2;     
    this.NOT_DEAL_INDENTIFIER = "<!-- unieapNotDeal -->"; 
    this.isAutoResize = false;
    
}
var unieap = new UniEAP();
