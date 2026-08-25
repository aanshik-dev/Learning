import{r as c,t,y as d}from"./index-9OuOb-5s.js";const m=({text:s,className:r,action:o,icon:a})=>{const i=c.useRef(null),x=c.useCallback(e=>{const l=i.current;if(!l)return;const n=l.getBoundingClientRect(),u=e.clientX-(n.left+n.width/2),f=e.clientY-(n.top+n.height/2);l.style.transform=`translate(${u*.35}px, ${f*.35}px)`},[]),p=c.useCallback(()=>{const e=i.current;e&&(e.style.transform="translate(0, 0)")},[]);return t.jsxs("div",{children:[t.jsx("style",{children:`
          .Btn::before {
            background: #9900ff;
            content: "";
            position: absolute;
            top: 200%;
            left: -50%;
            z-index: 1;
            transition: all 0.4s ease-in-out;
            width: 100%;
            height: 400%;
            filter: blur(15px);
            transform: translate(-50%, -50%) rotate(60deg);
            }
            
            
          .Btn:hover::before {
            height: 10%;
            top: -10%;
            left: 110%;
          }

          .Btn span {
            position: relative;
            z-index: 5;
            color: white;
          }
        `}),t.jsxs("button",{ref:i,onMouseMove:x,onMouseLeave:p,className:`Btn py-2 px-5 text-base flex justify-center items-center gap-2.5 relative font-normal cursor-pointer overflow-hidden transition-transform duration-300 ease-out text-transparent rounded-xl sm:min-w-45 text-nowrap nunito-sans bg-linear-to-r from-[#8c00ff] from-60% to-[#3e0077] ${r}`,onClick:o,children:[t.jsx("span",{children:a}),t.jsx("span",{children:s})]})]})},b=({hPlain:s,hColor:r,className:o="",tagline:a})=>t.jsxs(d.div,{initial:{opacity:0,y:20},whileInView:{opacity:1,y:0},viewport:{once:!0},transition:{duration:.6},className:`text-center text-white pb-4 sm:pb-8 ${o}`,children:[t.jsxs("h3",{className:"text-3xl sm:text-5xl text-center league-spartan font-bold",children:[s," ",t.jsx("span",{className:"text-[#bb00ff]",children:r})]}),t.jsx("p",{className:"text-[16px] text-center pt-2 text-[#948597] px-10 sm:px-0",children:a})]});export{m as B,b as H};
