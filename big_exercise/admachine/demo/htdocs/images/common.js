function enterToTab() {
	if (event.srcElement.type != "button" && event.srcElement.type != "textarea" && event.keyCode == 13) {
		event.keyCode = 9;
	}
}
function goToPage(){
    if(document.forms[0].pagenumber.value!=""){
	  window.location=document.forms[0].pagenumber.value;
	}
}

function getSelectedRadioValue(radioElement) {
	var e = getSelectedRadio(radioElement);
	if(e != null)
		return e.value;
	return null;
}


function getSelectedRadio(radioId) {
	radios = getElement(radioId);
	
	if (radios == null) {
		return;
	}
	if (radios.length == undefined) {
		if(radios.checked)
			return radios;
	}
	for(var i = 0; i < radios.length; i++) {
		if(radios[i].checked)
			return radios[i];
	}
	return null;
}

function selectRadioByValue(radioElement, v) {
	if(radioElement == null)
		return;
	if(v == null)
	 	return;
	if(radioElement.length != undefined) {
		for(var i = 0; i < radioElement.length; i++) {
			if(radioElement[i].value == v) {
				radioElement[i].click();
				radioElement[i].focus();
				break;
			}
		}
	} else {
		if(radioElement.value == v) {
			radioElement.click();
			radioElement.focus();
		}
	}
}

function selectFirstRadio(radioId) {
	var radios = getElement(radioId);
	if (radios == null) {
		return;
	}
	if (radios.length == undefined) {
		radios.click();
		return;
	}
	radios[0].click();
}


function disableRadios(radioId, able) {
	radio = document.all[radioId];
	if (radio != null) {
		if (radio.length == undefined) {
			radio.disabled = able;
		} else {
			for (i = 0; i < radio.length; i++) {
				radio[i].disabled = able;
			}
		}
	}
}

function openWindow(url){
	window.open(url,'','left=100,top=100,width=800,height=500,toolbar=1,resizable=1,location=no,menubar=no');
}
function openWindowLocation(url){
	window.open(url,'','left=100,top=100,width=800,height=500,toolbar=1,resizable=1,location=yes,menubar=no,scrollbars=yes');
}

function getElement(id) {
	var element = id;
	if (typeof(id) == 'string')
    	element = document.all[id];
 	return element;
}
//修改记录，form（form对象）、chkElement（checkbox对象）、url(转向的URL)
 function modify(form,chkElement,url){
   		var flags=0;
        flags=getChkNumber(chkElement);
        if(flags==0){
          	alert("请选择要修改的记录！");
          	return;
        }
        if(flags>1){
          	alert("一次只能修改一条记录！");
          	return;
        }
        submitForm(form,unieap.WEB_APP_NAME+url); 
        
 }
 //批量删除，form（form对象）、chkElement（checkbox对象）、url(转向的URL)
 function batchDelete(form,chkElement,url){
    	var flags=0;
        flags=getChkNumber(chkElement);
        if(flags==0){
          	alert("请选择要删除的记录！");
          	return;
        }      
        if(confirm("确定要删除吗？"))
           submitForm(form,unieap.WEB_APP_NAME+url); 
        
    } 
 //提交form，form（form对象）、url(转向的URL)
 function submitForm(form,url){
        form.action= unieap.WEB_APP_NAME+url;
		form.submit();
        
 } 	 
 //取得选中element个数，chkElement（checkbox对象）
 function getChkNumber(chkElement){
         var flags=0;
         for(var i=0;i<chkElement.length;i++){
          	if(chkElement[i].checked==true){
            	flags++;
          	}
        }
        return flags;
        
 }
 //修改radio，chkElement（checkbox对象）
 function modiRadio(form,chkElement,url){
        var flags=0;
        flags=getChkNumber(chkElement);
        if(flags==0){
          	alert("请选择要修改的记录！");
          	return;
        }
        submitForm(form,unieap.WEB_APP_NAME+url); 
        
 }
 //全选
 function selectAll(chkElement){
         var flags=0;
         for(var i=0;i<chkElement.length;i++){
          	chkElement[i].checked=true;
        }
 } 
 //全不选
 function unSelectAll(chkElement){
         var flags=0;
         for(var i=0;i<chkElement.length;i++){
          	chkElement[i].checked=false;
        }

 } 	    
 function getPageContent(url){
    var objXMLReq = getObjXMLReq();
    objXMLReq.open("POST", url, false);
    objXMLReq.send("");
    var strResult = objXMLReq.responseText;
    return strResult;
 }
//取得XMLHttpRequest对象,基于AJAX技术
function getObjXMLReq(){
    var objXMLReq;
    // IE5 for the mac claims to support window.ActiveXObject, but throws an error when it's used
    if (window.ActiveXObject && !(navigator.userAgent.indexOf('Mac') >= 0 && navigator.userAgent.indexOf("MSIE") >= 0)){
        objXMLReq = new ActiveXObject("Microsoft.XMLHTTP");
    }
    //for Mozilla and Safari etc.
    else if (window.XMLHttpRequest){
        objXMLReq = new XMLHttpRequest();
    }
    return objXMLReq;
}