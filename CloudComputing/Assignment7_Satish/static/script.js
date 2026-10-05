// Automatically display the current year in the footer

const yearElement = document.getElementById("year");

const currentYear = new Date().getFullYear();

yearElement.textContent = currentYear;