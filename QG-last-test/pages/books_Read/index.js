//首先，将文档内容读入一个字符串或数组中。这可以通过AJAX请求或使用HTML5文件读取器来完成。
// 使用 AJAX 请求读取文本文件内容
let xhr = new XMLHttpRequest();
xhr.onreadystatechange = function() {
  if (xhr.readyState === 4 && xhr.status === 200) {
    let bookContent = xhr.responseText;
    // 将读入的文档内容设置为容器的innerHTML。此时，文档内容将被添加到浏览器DOM树中并成为可编辑的。
    document.getElementById('book-viewer').innerHTML = bookContent;
  }
};
xhr.open('GET', 'your-book.txt');
xhr.send();

// 然后，定义一个函数来计算每一页的高度，并计算出页面总数。
function calculatePageHeight() {
  let viewer = document.getElementById('book-viewer');
  let pageHeight = viewer.clientHeight;
  let lineHeight = parseInt(window.getComputedStyle(viewer).lineHeight);
  let pageCount = Math.ceil(viewer.scrollHeight / pageHeight);
  return {pageCount, lineHeight, pageHeight};
}

document.getElementById('book-viewer').innerHTML = bookContent;
// 根据页面总数生成一个包含所有页面的空的div容器。然后将每一页的内容从原始容器中解析到相应的页面容器中。
let pageInfo = calculatePageHeight();
let pageCount = pageInfo.pageCount;

for (let i = 0; i < pageCount; i++) {
    let pageDiv = document.createElement('div');
    pageDiv.className = 'book-page';
    pageDiv.style.height = pageInfo.pageHeight + 'px';
    pageDiv.style.lineHeight = pageInfo.lineHeight + 'px';

    let startOffset = i * pageInfo.pageHeight;
    let endOffset = Math.min(startOffset + pageInfo.pageHeight, viewer.textContent.length);

    let pageContent = viewer.textContent.substring(startOffset, endOffset);
    pageDiv.innerHTML = pageContent;

    document.getElementById('book-pages').appendChild(pageDiv);
}
// 根据分页后内容的高度，重新设置容器高度，以适应所有页面。
document.getElementById('book-viewer').style.height = (pageInfo.pageCount * pageInfo.pageHeight) + 'px';






























var reader = document.getElementById("reader");
var content = document.getElementById("content");
var pageNum = document.getElementById("page-num");
var paragraphs = getParagraphs(); // 获取段落数组

var currentPage = 1;
var totalPages = paragraphs.length;

// 初始化页面
renderPage(currentPage);

// 监听滚动事件
reader.addEventListener("scroll", function() {
  var currentPageBottom = currentPage * reader.clientHeight;
  if (reader.scrollTop >= currentPageBottom) {
    currentPage++;
    renderPage(currentPage);
  } else if (reader.scrollTop < currentPageBottom - reader.clientHeight) {
    currentPage--;
    renderPage(currentPage);
  }
});

// 获取段落数组
function getParagraphs() {
  var text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. Praesent egestas leo in pede. Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. Maecenas adipiscing ante non diam sodales hendrerit.";

  var lines = text.split(". "); // 将文本分割成行
  var paragraphs = [];
  var currentParagraph = "";

  for (var i = 0; i < lines.length; i++) {
    var line = lines[i].trim();
    if (currentParagraph !== "" && currentParagraph.length + line.length > 500) {
      paragraphs.push(currentParagraph);
      currentParagraph = "";
    }
    currentParagraph += line + ". ";
  }

  if (currentParagraph !== "") {
    paragraphs.push(currentParagraph);
  }

  return paragraphs;
}

// 渲染页面
function renderPage(page) {
  content.innerHTML = "";
  pageNum.textContent = "Page " + page + " of " + totalPages;

  var start = (page - 1) * 20;
  var end = start + 20;
  if (end > paragraphs.length) {
    end = paragraphs.length;
  }

  for (var i = start; i < end; i++) {
    var paragraph = paragraphs[i];
    var pageEl = document.createElement("div");
    pageEl.classList.add("page");
    pageEl.textContent = paragraph;
    content.appendChild(pageEl);
  }
}

