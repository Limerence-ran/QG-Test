    window.onload=function(){
        //post请求
        document.querySelector("#send").onclick= function(){
        var xmlhttp = new XMLHttpRequest();
        var obj = {
            "username":"qgstudio",
            "password":"qgstudio"
        };
        xmlhttp.open("POST", "http://119.91.210.79:3000/login", true);
        xhr.setRequestHeader("Content-type","application/json");
        
          // readyState == 4 为请求完成，status == 200为请求成功返回的状态
        xmlhttp.onreadystatechange = function(){
            if(xmlhttp.readyState == 4 && xmlhttp.status == 200){
                console.log(xmlhttp.responseText);
                alert("登陆成功！")
            }else{
                alert(this.status+"——用户名或密码错误，请重试！")
            }
        }
          xmlhttp.send(JSON.stringify(obj));  // 要发送的参数，要转化为json字符串发送给后端，后端就会接受到json对象
    }
    }
    

