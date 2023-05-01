window.addEventListener("load",function(){
/* 加载动画 */

/* 图书封面 */

/* 图书信息 */
// 获取DOM元素
var viewBookBtn = document.getElementById("view-book");
var addToFavoritesBtn = document.getElementById("add-to-favorites");
var commentsList = document.getElementById("comments-list");
var commentForm = document.getElementById("comment-form");

// 点击在线浏览按钮，打开书籍阅读页面
viewBookBtn.addEventListener("click", function() {
  // 在此处添加打开在线阅读页面的代码
});

// 点击加入收藏按钮，将书籍加入用户的收藏列表
addToFavoritesBtn.addEventListener("click", function() {
  // 在此处添加将书籍加入收藏列表的代码
});

// 提交评论表单
commentForm.addEventListener("submit", function(event) {
  event.preventDefault(); // 阻止表单默认提交行为
  var commentInput = document.getElementById("comment");
  var commentText = commentInput.value;
  var newComment = createCommentElement(commentText);
  commentsList.appendChild(newComment);
  commentInput.value = ""; // 清空评论输入框
});

// 创建新评论元素


/* 管理员的删除权限  */

/* 收藏书架 */
addToFavoritesBtn.addEventListener("click", function() {
  var book = {
    title: "JavaScript高级程序设计",
    author: "Nicholas C",
    pages: 960,
    price: 109
  };
  var favorites = JSON.parse(localStorage.getItem("favorites")) || [];
  favorites.push(book);
  localStorage.setItem("favorites", JSON.stringify(favorites));
});

/* 评论区*/
commentForm.addEventListener("submit", function(event) {
  event.preventDefault(); // 阻止表单默认提交行为
  var commentInput = document.getElementById("comment");
  var commentText = commentInput.value;
  var xhr = new XMLHttpRequest();
  xhr.open("POST", "/api/comments", true);
  xhr.setRequestHeader("Content-type", "application/json");
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      var newComment = createCommentElement(commentText);
      commentsList.appendChild(newComment);
      commentInput.value = ""; // 清空评论输入框
    }
  };
  var data = {
    book: "JavaScript高级程序设计",
    comment: commentText
  };
  xhr.send(JSON.stringify(data));
});


})