// Fonction de gestion de la molette de la souris
function handleMouseWheel(event) {
    if (event.deltaY > 0) {
        // Faire défiler vers le bas
        window.scrollBy(0, 100); // Vous pouvez ajuster la valeur 100 selon votre préférence
    } else {
        // Faire défiler vers le haut
        window.scrollBy(0, -100); // Vous pouvez ajuster la valeur -100 selon votre préférence
    }

    // Empêcher le comportement de défilement par défaut
    event.preventDefault();
}

// Ajouter un écouteur d'événements pour la molette de la souris
window.addEventListener("wheel", handleMouseWheel);
