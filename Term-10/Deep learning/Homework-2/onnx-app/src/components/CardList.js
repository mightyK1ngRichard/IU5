import React from "react";
import { CARDS, CLASS_COLORS } from "../data/cards";
import "../style/CardList.css";

const CLASS_LABELS = {
  raspberry:  "Малина",
  strawberry: "Клубника",
  blackberry: "Ежевика",
};

const CardList = ({ matchedIds = [] }) => {
  const classes = ["raspberry", "strawberry", "blackberry"];

  return (
    <div className="cardlist-root">
      {classes.map((cls) => (
        <div className="cardlist-section" key={cls}>
          <div className="cardlist-section-title" style={{ borderColor: CLASS_COLORS[cls] }}>
            <span className="cardlist-dot" style={{ background: CLASS_COLORS[cls] }} />
            {CLASS_LABELS[cls]}
          </div>
          <div className="cardlist-grid">
            {CARDS.filter((c) => c.className === cls).map((card) => {
              const isMatch = matchedIds.includes(card.id);
              return (
                <div
                  key={card.id}
                  className={`card ${isMatch ? "card--match" : ""}`}
                  style={{ "--cls-color": CLASS_COLORS[cls] }}
                >
                  <div className="card-emoji">{card.emoji}</div>
                  <div className="card-name">{card.name}</div>
                  {isMatch && <div className="card-badge">✓ совпадение</div>}
                </div>
              );
            })}
          </div>
        </div>
      ))}
    </div>
  );
};

export default CardList;
