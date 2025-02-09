import { loadHomePage } from "./loader.js";

export let connectWss;

export function initWebSocket() {
    if (!connectWss) {  
        connectWss = new WebSocket(`wss://${window.location.host}/ws/logs/`);

        connectWss.onopen = () => {
            //console.log("WebSocket connected!");
        };

        connectWss.onmessage = (e) => {
            let data = JSON.parse(e.data)
            //console.log("deconnect : ", data);
            if (data.event === "two_connection")
            {
                const csrfToken = document.cookie.match(/csrftoken=([^;]+)/)?.[1];
                fetch("/logout/", {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/json",
                        "X-CSRFToken": csrfToken,
                    },
                    credentials: "same-origin",
                })
                    .then((response) => {
                        if (response.ok) {
                            //console.log("Logged out successfully");
                            if (connectWss) {
                                connectWss.close();
                                //console.log("WebSocket closed.");
                            }
                            loadHomePage();
                        } else {
                            console.error("Error logging out");
                        }
                    })
                    .catch((error) => console.error("Error logging out:", error));;
            }
                
        };

        connectWss.onclose = () => {
            //console.log("WebSocket closed.");
        };

        connectWss.onerror = (error) => {
            console.error("WebSocket error:", error);
        };
    }
}
