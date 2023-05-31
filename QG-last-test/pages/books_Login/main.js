//入口函数
window.addEventListener("load",function(){
//动态切换登录和注册页面
  var link_reg = document.querySelector("#link-reg");
  var link_login = document.querySelector("#link-login");
  var login_box = document.querySelector(".login-box");
  var reg_box = document.querySelector(".reg-box");

  link_reg.onclick = function(){
    login_box.style.display = "none";
    reg_box.style.display = "block";
  }
  link_login.onclick = function(){
    reg_box.style.display = "none";
    login_box.style.display = "block";
  }

// 获取表单元素和按钮元素
const form = document.querySelector('.form');
const sendButton = form.querySelector('.send');

// 给发送按钮添加点击事件监听器
sendButton.addEventListener('click', function(e) {
  // 阻止默认提交行为
    e.preventDefault();

  // 获取用户名和密码
    const username = form.querySelector('.form input[name="username"]').value;
    const password = form.querySelector('.form input[name="password"]').value;
    const repassword = form.querySelector('.form input[name="repassword"]').value

    //注册功能
    if (password !== repassword) {
      alert('两次输入的密码不一致');
      return;
    }
  
    fetch('/register', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({
        username,
        password
      })
    })
    .then(res => res.json())
    .then(data => {
      if (data.code === 0) {
        alert('注册成功');
      } else {
        alert(data.msg);
      }
    })

    //登录功能
    if(localStorage.getItem('token')){
        /*在这个代码中，首先获取了发送按钮元素，并给发送按钮添加了一个点击事件监听器。
        当用户点击发送按钮后，代码会获取输入框中的用户名和密码，并使用 fetch 函数发送一个 POST 请求到服务器上的 /login 路径。
        需要注意的是，在这个请求头中加入了一个 Authorization 字段，其中带上了前面从本地存储中获取到的 token。
        这样，服务器就能够验证客户端的身份信息了。*/
          // 获取 token
    const token = localStorage.getItem('token');

  // 发送 POST 请求（带上 token）
    fetch('/login', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Authorization': `Bearer ${token}`
    },
    body: JSON.stringify({username, password})
    })
    .then(response => response.json())
    .then(data => console.log(data))
    .catch(error => console.error(error));
    }
    else{
        /*在这个代码中，首先获取了表单元素和发送按钮元素，并给发送按钮添加了一个点击事件监听器。
        当用户点击发送按钮后，代码会获取输入框中的用户名和密码，并使用 fetch 函数发送一个 POST 请求到服务器上的 /login 路径。
        这个请求中使用了 JSON 格式的数据，将用户名和密码作为请求体发送给服务器。
        当服务器成功验证用户信息后，会向客户端发送一个包含 token 的响应。
        在这个代码中，我们在 then 方法中获取了这个 token，并使用 localStorage.setItem() 函数将其存储在本地存储中。
        最后，代码跳转到首页或其他需要登录才能访问的页面。
        接下来，我们可以在每次向服务器发送请求时都带上这个 token 作为身份验证信息。
        以下是如何用原生 JavaScript 实现每次请求都带上 token 的代码：*/
        
    // 发送 POST 请求（没有 token）
    fetch('/login', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json'
    },
    body: JSON.stringify({username, password})
    })
    .then(response => response.json())
    .then(data => {
    // 保存 token 到本地存储中
    localStorage.setItem('token', data.token);

    // 跳转到首页或其他需要登录才能访问的页面
    window.location.href = '../books_Main/index.html';
    })
    .catch(error => console.error(error));
    };
    })


})



