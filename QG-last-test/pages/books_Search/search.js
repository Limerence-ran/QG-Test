// 借助原生 JavaScript 的一些特性和 API 实现搜索框的搜索和热词提示功能，具体实现步骤如下：
// 1.为搜索框绑定键盘事件监听。
// 2.根据输入内容发起请求，获取匹配到的数据并渲染到页面上。
// 3.实现热词提示功能，可以在搜索框下方展示最近热门搜索。
// 4.在输入框获得焦点时显示热词提示，失去焦点时隐藏。

// 获取搜索关键字
function getKeywords(str) {
  // 可以根据实际需求修改搜索规则
  return str.trim().toLowerCase();
}

// 搜索匹配结果
function search(keyword) {
  const xhr = new XMLHttpRequest();
  xhr.open('GET', '/search?keyword=' + encodeURIComponent(keyword), true);
  xhr.send(null);
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      //拿到数据
      let data = JSON.parse(xhr.responseText);
      //传递数据
      renderResult(data);
    }
  };
}

// 渲染搜索结果
function renderResult(data) {
  //获取结果框DOM
  const result_container = document.getElementById('result-container');

  result_container.innerHTML = '';

  for (var i = 0; i < data.length; i++) {
    // 创造div
    const item = document.createElement('div');
    item.innerHTML = data[i];
    result_container.appendChild(item);
  }
}

// 获取热门搜索
function getHotKeywords() {
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/hot_keywords', true);
  xhr.send(null);
  xhr.onreadystatechange = function() {
    if (xhr.readyState === 4 && xhr.status === 200) {
      let data = JSON.parse(xhr.responseText);
      renderHotKeywords(data);
    }
  };
}

// 渲染热门搜索
function renderHotKeywords(data) {
  const container = document.getElementById('hot-keywords');
  container.innerHTML = '';

  for (var i = 0; i < data.length; i++) {
    const item = document.createElement('div');
    item.innerHTML = data[i];
    container.appendChild(item);
  }
}

// 绑定事件监听
window.onload = function() {

  //获取搜索框DOM
  const search_input = document.getElementById('search-input');
  //获取热词框DOM
  const hotKeywords = document.getElementById('hot-keywords');

  // 输入框获得焦点时显示热词提示
  search_input.addEventListener('focus', function() {
    hotKeywords.style.display = 'block';
  });

  // 输入框失去焦点时隐藏热词提示
  search_input.addEventListener('blur', function() {
    hotKeywords.style.display = 'none';
  });

  // 编写防抖函数，避免多次请求
  function debounce(fn, delay) {
    let timer = null;
    return function() {
      let context = this;
      let args = arguments;
      clearTimeout(timer);
      timer = setTimeout(function() {
        fn.apply(context, args);
      }, delay);
    };
  }

  // 输入内容时发起模糊搜索请求
  search_input.addEventListener('input',debounce(function(e) {
      let keyword = getKeywords(e.target.value);
      search(keyword);
    }, 500)
  );

  // 获取并渲染热门搜索关键字
  getHotKeywords();
};


