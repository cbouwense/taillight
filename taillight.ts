const asColor = (str: string, document: Document) => {
    const thereIsAVariable = Array.from(document.styleSheets[0].cssRules).find((rule) => rule.cssText.includes(`--${str}`));
    return thereIsAVariable ? `var(--${str})` : `#${str}`;
};

// Add a percent sign when the class name has a number without a unit.
// \D means "all non-numeric", so negating it means "if all numeric".
const asSize = (str: string) => !str.match(/\D/) ? str + "%": str;

const abbrevAsProperty: Record<string, string> = {
    "b": "border",
    "bb": "border-bottom",
    "bl": "border-left",
    "br": "border-right",
    "brad": "border-radius",
    "bt": "border-top",
    "bg": "background-color",
    "bottom": "bottom",
    "c": "color",
    "fs": "font-size",
    "gap": "gap",
    "h": "height",
    "left": "left",
    "m": "margin",
    "mb": "margin-bottom",
    "ml": "margin-left",
    "mr": "margin-right",
    "mt": "margin-top",
    "p": "padding",
    "pb": "padding-bottom",
    "pl": "padding-left",
    "pr": "padding-right",
    "pt": "padding-top",
    "right": "right",
    "top": "top",
    "w": "width",
    "z": "z-index",
}

const rule = (className: string, abbrev: string, values: string[], important: boolean) => {
    const valuesAsSizes = values.map(asSize).join(" ");
    
    let rule = `.${className} `;
    switch (abbrev) {
    case "absolute":
        rule += `{ position: absolute; }`;
        break;
    case "alignStart":
        rule += `{ align-items: flex-start; }`;
        break;
    case "alignEnd":
        rule += `{ align-items: flex-end; }`;
        break;
    case "alignCenter":
        rule += `{ align-items: center; }`;
        break;
    case "alignBaseline":
        rule += `{ align-items: baseline; }`;
        break;
    case "alignStretch":
        rule += `{ align-items: stretch; }`;
        break;
    case "b":
        rule += `{ border: ${asSize(values[0])} ${values[1]} ${asColor(values[2], document)}; }`;
        break;
    case "bg":
        rule += `{ background-color: ${asColor(values[0], document)}; }`;
        break;
    case "bx":
        rule += `{
        border-left: ${asSize(values[0])} ${values[1]} ${asColor(values[2], document)};
        border-right: ${asSize(values[0])} ${values[1]} ${asColor(values[2], document)};
        }`;
        break;
    case "by":
        rule += `{
        border-top: ${asSize(values[0])} ${values[1]} ${asColor(values[2], document)};
        border-bottom: ${asSize(values[0])} ${values[1]} ${asColor(values[2], document)};
        }`;
        break;
    case "c":
        rule += `{ color: ${asColor(values[0], document)}; }`;
        break;
    case "fixed":
        rule += `{ position: fixed; }`;
        break;
    case "flex":
        rule += `{ display: flex; }`;
        break;
    case "justifyNormal":
        rule += "{ justify-content: normal; }";
        break;
    case "justifyStart":
        rule += "{ justify-content: flex-start; }";
        break;
    case "justifyEnd":
        rule += "{ justify-content: flex-end; }";
        break;
    case "justifyCenter":
        rule += "{ justify-content: center; }";
        break;
    case "justifyBetween":
        rule += "{ justify-content: space-between; }";
        break;
    case "justifyAround":
        rule += "{ justify-content: space-around; }";
        break;
    case "justifyEvenly":
        rule += "{ justify-content: space-evenly; }";
        break;
    case "justifyStretch":
        rule += "{ justify-content: stretch; }";
        break;
    case "mx":
        rule += `{ margin-left: ${valuesAsSizes}; margin-right: ${valuesAsSizes}; }`;
        break;
    case "my":
        rule += `{ margin-top: ${valuesAsSizes}; margin-bottom: ${valuesAsSizes}; }`;
        break;
    case "px":
        rule += `{ padding-left: ${valuesAsSizes}; padding-right: ${valuesAsSizes}; }`;
        break;
    case "py":
        rule += `{ padding-top: ${valuesAsSizes}; padding-bottom: ${valuesAsSizes}; }`;
        break;
    case "relative":
        rule += `{ position: relative; }`;
        break;
    case "z":
        rule += `{ z-index: ${values[0] === "top" ? "99999" : values[0]} }`;
        break;
    default:
        rule += `{ ${abbrevAsProperty[abbrev]}: ${valuesAsSizes}; }`;
        break;
    }
    
    if (important) rule = rule.replace("; }", " !important; }");

    console.log(rule);
    return rule;
}

window.addEventListener('DOMContentLoaded', function() {
    const stylesheet = document.styleSheets[0];
    const allClasses = new Set<string>(
        Array.from(document.querySelectorAll('*'))
            .filter((el) => el.classList.length > 0)
            .reduce((set, element) => {
                element.className.split(' ').forEach(className => set.add(className));
                return set;
            }, new Set<string>())
    );

    stylesheet.insertRule(".default { display: inherit; }");
    stylesheet.insertRule(".tablet { display: none; }");
    stylesheet.insertRule(".computer { display: none; }");
    stylesheet.insertRule(".ultraWide { display: none; }");
    const tabletMediaIndex = stylesheet.insertRule(`@media screen and (min-width: 768px) {
        .default { display: none; }
        .tablet { display: inherit; }
        .computer { display: none; }
        .ultraWide { display: none; }
    }`, stylesheet.cssRules.length);
    const computerMediaIndex = stylesheet.insertRule(`@media screen and (min-width: 992px) {
        .default { display: none; }
        .tablet { display: none; }
        .computer { display: inherit; }
        .ultraWide { display: none; }
    }`, stylesheet.cssRules.length);
    const ultraWideMediaIndex = stylesheet.insertRule(`@media screen and (min-width: 3440px) {
        .default { display: none; }
        .tablet { display: none; }
        .computer { display: none; }
        .ultraWide { display: inherit; }
    }`, stylesheet.cssRules.length);
    
    const tabletMediaQuery = stylesheet.cssRules[tabletMediaIndex] as CSSMediaRule;
    const computerMediaQuery = stylesheet.cssRules[computerMediaIndex] as CSSMediaRule;
    const ultraWideMediaQuery = stylesheet.cssRules[ultraWideMediaIndex] as CSSMediaRule;
    
    const classesNotRequiringRuleGeneration = ["tablet", "computer", "ultraWide"];
    const classRequiresRuleGen = (className: string) => !classesNotRequiringRuleGeneration.includes(className);

    [...allClasses]
    .filter(classRequiresRuleGen)
    .forEach(className => {
        const important = className.endsWith("_imp");
        if (className.startsWith("t_")) {
        let [name, ...values] = className.split("_")[1].split("-");
        if (important) {
            values[values.length-1] = values[values.length-1].split("_imp")[0];
        }
        tabletMediaQuery.insertRule(rule(className, name, values, important));
        } else if (className.startsWith("c_")) {
        let [name, ...values] = className.split("_")[1].split("-");
        if (important) {
            values[values.length-1] = values[values.length-1].split("_imp")[0];
        }
        computerMediaQuery.insertRule(rule(className, name, values, important));
        } else if (className.startsWith("uw_")) {
        let [name, ...values] = className.split("_")[1].split("-");
        if (important) {
            values[values.length-1] = values[values.length-1].split("_imp")[0];
        }
        ultraWideMediaQuery.insertRule(rule(className, name, values, important));
        } else {
        let [name, ...values] = className.split("-");
        if (important) {
            values[values.length-1] = values[values.length-1].split("_imp")[0];
        }
        stylesheet.insertRule(rule(className, name, values, important));
        }
    });
});