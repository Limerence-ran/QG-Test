// 在原生JavaScript中，可以使用window.location对象来获取当前页面的URL地址，并根据URL地址来实现路由配置。

// 首先在每个HTML页面中都需要引入同一个JS文件，该JS文件负责实现路由功能。
// 接着通过监听window对象的hashchange事件（即链接中#部分发生变化时触发的事件），来判断应该展示哪个页面。

// 路由配置
var routes = {
  '/': '../pages/books_Main/index.html',
  '/login': '../pages/books_Login/index.html',
  '/detail': '../pages/books_Detail/index.html',
  '/read':'../pages/books_Read/index.html',
  '/me':'../pages/books_Me/index.html',
  '/search':'../pages/books_Search/index.html'
};

// 显示对应页面的函数并实现页面加载动画
//要实现页面加载动画，可以在render函数中添加一些代码，来显示一个加载中的提示
function render(route) {
  var contentDiv = document.getElementById('content');
  contentDiv.innerHTML = '<div class="loading">加载中...</div>'; // 显示加载中的提示

  var xhr = new XMLHttpRequest();
  xhr.open('GET', routes[route], true);
  xhr.onreadystatechange = function() {
      if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
          contentDiv.innerHTML = xhr.responseText;
      } else if (xhr.readyState === XMLHttpRequest.DONE && xhr.status !== 200) {
          contentDiv.innerHTML = '<div class="error">加载失败，请稍后再试！</div>'; // 显示加载失败的提示
      }
  };
  xhr.send();
}
// 在上述代码中，我们增加了一个class为"loading"的DIV来展示加载中的提示。
// 当XMLHttpRequest请求完成后，无论成功或失败，都会触发onreadystatechange事件，并根据状态码来判断是否加载成功。
// 如果出现加载失败的情况，我们则会显示一个class为"error"的DIV来展示错误信息



// 监听hashchange事件
window.addEventListener('hashchange', function() {
  var route = window.location.hash.slice(1);
  render(route);
});

// 默认显示首页
render('/');


// 先定义了一个对象routes，用来存储不同路由对应的页面路径
// 然后定义了一个函数render，该函数通过发送XMLHttpRequest请求获取相应的HTML页面，并将其显示在页面上
// 添加了一个监听器来监听hashchange事件。当URL地址中的#部分发生变化时，会触发该事件，我们可以通过获取当前URL中的#部分，并将其作为参数传递给render函数，从而实现页面的切换
// 最后，在页面加载完成时，我们默认将首页展示出来