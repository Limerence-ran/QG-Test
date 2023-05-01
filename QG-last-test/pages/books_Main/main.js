window.addEventListener('load',function() {
    // 页面加载动画
    var loading = document.getElementById('loading');
    var mask = document.getElementById('mask');
    setTimeout(function() {
        loading.style.display = 'none';
        mask.style.display = 'none';
    }, 2000);

    function goToPage(url) {
    loading.style.display='block'; // 显示加载动画
    mask.style.display='block'//显示遮罩层
    setTimeout(function() {
        location.href=url; // 跳转到指定页面
    }, 2000);
  }

    // Tab栏切换
    var limodules = document.querySelector('.li-module');
    var lis = limodules.querySelectorAll('li');
    var items = document.querySelectorAll('.item');

    lis[0].classList.add('current-module');

    for (let i = 0; i < lis.length-2; i++) {
    // 添加自定义属性
      lis[i].index = i;
      
    // 主页、分类、排行、书架绑定点击事件
      lis[i].onclick = function () {

        for (let i = 0; i < lis.length-2; i++) {
              lis[i].classList.remove('current-module');
              items[i].style.display = 'none';
          }

          this.classList.add('current-module');
          var index = this.index;
          items[index].style.display = 'block';
          }
    }

    // 搜索框
    // 获取搜索关键字
function getKeywords(str) {
  // 可以根据实际需求修改搜索规则
  return str.trim().toLowerCase();
}

// 搜索匹配结果
function search(keyword) {
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/search?keyword=' + encodeURIComponent(keyword), true);
  xhr.send(null);
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      var data = JSON.parse(xhr.responseText);
      renderResult(data);
    }
  };
}

// 渲染搜索结果
function renderResult(data) {
  var container = document.getElementById('result-container');
  container.innerHTML = '';

  for (var i = 0; i < data.length; i++) {
    var item = document.createElement('div');
    item.innerHTML = data[i];
    container.appendChild(item);
  }
}

// 获取热门搜索
function getHotKeywords() {
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/hot_keywords', true);
  xhr.send(null);
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      var data = JSON.parse(xhr.responseText);
      renderHotKeywords(data);
    }
  };
}

// 渲染热门搜索
function renderHotKeywords(data) {
  var container = document.getElementById('hot-keywords');
  container.innerHTML = '';

  for (var i = 0; i < data.length; i++) {
    var item = document.createElement('div');
    item.innerHTML = data[i];
    container.appendChild(item);
  }
}

// 绑定事件监听
window.onload = function() {
  var input = document.getElementById('search-input');
  var hotKeywords = document.getElementById('hot-keywords');

  // 输入框获得焦点时显示热词提示
  input.addEventListener('focus', function() {
    hotKeywords.style.display = 'block';
  });

  // 输入框失去焦点时隐藏热词提示
  input.addEventListener('blur', function() {
    hotKeywords.style.display = 'none';
  });

  // 编写防抖函数，避免多次请求
  function debounce(fn, delay) {
    var timer = null;
    return function() {
      var context = this;
      var args = arguments;
      clearTimeout(timer);
      timer = setTimeout(function() {
        fn.apply(context, args);
      }, delay);
    };
  }

  // 输入内容时发起模糊搜索请求
  input.addEventListener(
    'input',
    debounce(function(e) {
      var keyword = getKeywords(e.target.value);
      search(keyword);
    }, 500)
  );

  // 获取并渲染热门搜索关键字
  getHotKeywords();
};


    // //管理绑定点击事件
    // lis[4].onclick = function(){
    //   if(/*判断账户是否为管理员 */){
    //     //把display属性改为block；
    //   }else{
    //     alert("用户权限不足，功能无法使用");
    //   }
    // }


    // 轮播图
    // 获取左右按钮和图片列表
    let oLeft = document.querySelector(".left");
    let oRight = document.querySelector(".right");
    let oImgList = document.querySelector(".img-list");

    // 克隆第一张图片
    let cloneFirstImg = oImgList.firstElementChild.cloneNode();
    // 克隆第一张图片
    let cloneLastImg = oImgList.lastElementChild.cloneNode();

    // 将第一张图片添加至图片列表的末尾
    oImgList.appendChild(cloneFirstImg);
    // 将最后一张图片添加至图片列表的首部
    oImgList.insertBefore(cloneLastImg,oImgList.querySelector("img"));

    // 图片索引 代表当前是第几张图片  index:1代表第一张图片  
    let index = 1;

    // 设置函数节流锁
    let lock = true;

    //设置右按钮的功能
    function handleRightBtn() {
      if (!lock) return;
      index++;
      oImgList.style.transform = "translateX("+ index * -1226 + "px)";
      oImgList.style.transition = "0.5s ease";
      if (index === 6) {//切换完之后再跳转
        index = 1; //轮播完最后一张图后重置index的值
        setTimeout(() => {
          oImgList.style.transform = "translateX(" + index * -1226 + "px)";
          //取消过渡 500毫秒之后切换最后一张
          oImgList.style.transition = "none";
        }, 500);     
      }

      // 设置小圆点的高亮
      setCircles();
      // 关锁
      lock = false;
      setTimeout(() => {
        lock = true;
      }, 500);
    }

    //设置左按钮的功能
    function handleLeftBtn() {
      if (!lock) return;
        index--;
      if (index === 0) {//切换完之后再跳转
        oImgList.style.transition = "none";
        oImgList.style.transform = "translateX(" + index * -1226 + "px)";
        //无过渡切换到最后一张
        index = 5;
        //恢复过渡
        oImgList.style.transition = "0.5s ease";
        setTimeout(() => {
          oImgList.style.transform = "translateX(" + index * -1226 + "px)";
          //取消过渡 500毫秒之后切换最后一张
          oImgList.style.transition = "none";
        }, 500);     
        } else {
        oImgList.style.transition = "0.5s ease";
        oImgList.style.transform = "translateX(" + index * -1226 + "px)";
      }

      // 设置小圆点的高亮
      setCircles();

      lock = false;
      setTimeout(() => {
        lock = true;
      }, 500);
    }

    // 右按钮的实现
    oRight.addEventListener("click", handleRightBtn);

    // 左按钮的实现  瞬间切换到假图然后拉到真实最后一张图片
    oLeft.addEventListener("click", handleLeftBtn);
    
    

    // 获取五个小圆点
    const circles = document.querySelectorAll(".circle");

    // 小圆点高亮的显示
    function setCircles() {
      for (let i = 0; i < circles.length; i++) {
        if (i+1 === index) {
          circles[i].classList.add("active");
        } else {
          circles[i].classList.remove("active");
        }
      }
    }

    // 小圆点点击切换图片 使用事件代理
    const oCircle = document.querySelector(".circle-list");
    oCircle.addEventListener("click", (e) => {
      // 当点击小圆点的时候
      if (e.target.nodeName.toLowerCase() === "li") {
        // 当前元素的data-n和index 一一对应
        const n = Number(e.target.getAttribute("data-n"));
        index = n;
        setCircles();
        oImgList.style.transition = "0.5s ease";
        oImgList.style.transform = "translateX("+ index * -1226 + "px)";
      }
    });

    // 自动轮播
    let autoplay = setInterval(handleRightBtn, 3000);
    const oWrap = document.getElementById("wrap");
    // 移入停止轮播
    oWrap.addEventListener("mouseenter", () => {
      clearInterval(autoplay);
    });
    // 移出继续轮播
    oWrap.addEventListener("mouseleave", () => {
      // 设表先关
      clearInterval(autoplay);
      autoplay = setInterval(handleRightBtn, 2000);
  })
































})
