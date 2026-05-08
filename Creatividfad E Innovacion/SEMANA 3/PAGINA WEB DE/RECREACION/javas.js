function toggleMenu() {
    var menu = document.getElementById("side-menu");
    var content = document.querySelector(".content");

    if (menu.style.width === "0px" || menu.style.width === "") {
        menu.style.width = "250px"; // abrir
        content.style.marginLeft = "250px";
    } else {
        menu.style.width = "0"; // cerrar
        content.style.marginLeft = "0";
    }
}

// 🔹 Cerrar el menú al hacer clic en cualquier enlace dentro de él
document.addEventListener("DOMContentLoaded", function() {
    var links = document.querySelectorAll("#side-menu a");
    var menu = document.getElementById("side-menu");
    var content = document.querySelector(".content");

    links.forEach(function(link) {
        link.addEventListener("click", function() {
            menu.style.width = "0";
            content.style.marginLeft = "0";
        });
    });
});

//BOTON QUE MUESTRA Y OCULTA CONTENIDO
function toggleInfo() {
  const info = document.getElementById("info");
  info.classList.toggle("open");
}
 
//BARRA ANIMADA

window.addEventListener("scroll", () => {
  const scrollTop = window.scrollY; // cuánto has bajado
  const docHeight = document.documentElement.scrollHeight - window.innerHeight;
  const scrollPercent = (scrollTop / docHeight) * 100;

  document.getElementById("progress").style.width = scrollPercent + "%";
});
