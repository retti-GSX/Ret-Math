
document.addEventListener('DOMContentLoaded', function() {
    const navLinks = document.querySelectorAll('nav ul li a');
    const sections = document.querySelectorAll('section');
    
    navLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            const targetId = this.getAttribute('href');
            const targetSection = document.querySelector(targetId);
            
            if (targetSection) {
                targetSection.scrollIntoView({
                    behavior: 'smooth'
                });
                
                history.pushState(null, null, targetId);
            }
        });
    });
    
    window.addEventListener('scroll', function() {
        let currentSection = '';
        
        sections.forEach(section => {
            const sectionTop = section.offsetTop;
            const sectionHeight = section.clientHeight;
            
            if (window.scrollY >= (sectionTop - 200)) {
                currentSection = section.getAttribute('id');
            }
        });
        
        navLinks.forEach(link => {
            link.classList.remove('active');
            if (link.getAttribute('href') === '#' + currentSection) {
                link.classList.add('active');
            }
        });
    });
    
    highlightCodeBlocks();
    
    setupSearch();
    
    setupTooltips();
    
    addLanguageAttributes();
});

function highlightCodeBlocks() {
    const codeBlocks = document.querySelectorAll('.code-block pre');
    
    codeBlocks.forEach(block => {
        let code = block.textContent;
        
        code = code.replace(/\b#include\b/g, '<span class="keyword">#include</span>');
        code = code.replace(/\bnamespace\b/g, '<span class="keyword">namespace</span>');
        code = code.replace(/\busing\b/g, '<span class="keyword">using</span>');
        code = code.replace(/\bclass\b/g, '<span class="keyword">class</span>');
        code = code.replace(/\btemplate\b/g, '<span class="keyword">template</span>');
        code = code.replace(/\btypename\b/g, '<span class="keyword">typename</span>');
        code = code.replace(/\bconst\b/g, '<span class="keyword">const</span>');
        code = code.replace(/\bstatic\b/g, '<span class="keyword">static</span>');
        code = code.replace(/\breturn\b/g, '<span class="keyword">return</span>');
        code = code.replace(/\bvoid\b/g, '<span class="keyword">void</span>');
        code = code.replace(/\bint\b/g, '<span class="keyword">int</span>');
        code = code.replace(/\bfloat\b/g, '<span class="keyword">float</span>');
        code = code.replace(/\bdouble\b/g, '<span class="keyword">double</span>');
        code = code.replace(/\bbool\b/g, '<span class="keyword">bool</span>');
        code = code.replace(/\bif\b/g, '<span class="keyword">if</span>');
        code = code.replace(/\belse\b/g, '<span class="keyword">else</span>');
        code = code.replace(/\bfor\b/g, '<span class="keyword">for</span>');
        code = code.replace(/\bwhile\b/g, '<span class="keyword">while</span>');
        code = code.replace(/\bVector2\b/g, '<span class="type">Vector2</span>');
        code = code.replace(/\bVector3\b/g, '<span class="type">Vector3</span>');
        code = code.replace(/\bVector4\b/g, '<span class="type">Vector4</span>');
        code = code.replace(/\bMatrix2x2\b/g, '<span class="type">Matrix2x2</span>');
        code = code.replace(/\bMatrix3x3\b/g, '<span class="type">Matrix3x3</span>');
        code = code.replace(/\bMatrix4x4\b/g, '<span class="type">Matrix4x4</span>');
        code = code.replace(/\bQuaternion\b/g, '<span class="type">Quaternion</span>');
        code = code.replace(/\bSphere\b/g, '<span class="type">Sphere</span>');
        code = code.replace(/\bRay\b/g, '<span class="type">Ray</span>');
        code = code.replace(/\bPlane\b/g, '<span class="type">Plane</span>');
        code = code.replace(/\bAABB\b/g, '<span class="type">AABB</span>');
        code = code.replace(/\bOBB\b/g, '<span class="type">OBB</span>');
        code = code.replace(/\bTriangle\b/g, '<span class="type">Triangle</span>');
        code = code.replace(/\bCircle\b/g, '<span class="type">Circle</span>');
        code = code.replace(/\bRect\b/g, '<span class="type">Rect</span>');
        code = code.replace(/\bCapsule\b/g, '<span class="type">Capsule</span>');
        code = code.replace(/\bColor\b/g, '<span class="type">Color</span>');
        code = code.replace(/\bTransform\b/g, '<span class="type">Transform</span>');
        code = code.replace(/\bRandom\b/g, '<span class="type">Random</span>');
        code = code.replace(/\bInterpolation\b/g, '<span class="type">Interpolation</span>');
        code = code.replace(/\bIntersection\b/g, '<span class="type">Intersection</span>');
        
        code = code.replace(/\b\d+\.\d+f\b/g, '<span class="number">$&</span>');
        code = code.replace(/\b\d+\.\d+\b/g, '<span class="number">$&</span>');
        code = code.replace(/\b\d+\b/g, '<span class="number">$&</span>');
        
        code = code.replace(/\/\/[^\n]*/g, '<span class="comment">$&</span>');
        code = code.replace(/\/\*.*?\*\//g, '<span class="comment">$&</span>');
        
        code = code.replace(/"[^"]*"/g, '<span class="string">$&</span>');
        code = code.replace(/'[^']*'/g, '<span class="string">$&</span>');
        
        code = code.replace(/\b\w+\(/g, '<span class="function">$&</span>');
        
        block.innerHTML = code;
    });
    
    const style = document.createElement('style');
    style.textContent = `
        .keyword { color: #569cd6; font-weight: bold; }
        .type { color: #4ec9b0; }
        .number { color: #b5cea8; }
        .comment { color: #6a9955; font-style: italic; }
        .string { color: #ce9178; }
        .function { color: #dcdcaa; }
        .active { background-color: #16a085 !important; }
    `;
    document.head.appendChild(style);
}

function setupSearch() {
    const searchInput = document.createElement('input');
    searchInput.type = 'text';
    searchInput.placeholder = 'Search documentation...';
    searchInput.id = 'search-input';
    searchInput.title = 'Type to search through the documentation';
    
    const searchContainer = document.createElement('div');
    searchContainer.id = 'search-container';
    
    searchContainer.appendChild(searchInput);
    
    const header = document.querySelector('header');
    header.appendChild(searchContainer);
    
    searchInput.addEventListener('input', function() {
        const searchTerm = this.value.toLowerCase();
        const sections = document.querySelectorAll('section');
        const components = document.querySelectorAll('.component');
        
        let visibleSections = 0;
        
        sections.forEach(section => {
            const text = section.textContent.toLowerCase();
            if (text.includes(searchTerm)) {
                section.style.display = 'block';
                visibleSections++;
            } else {
                section.style.display = 'none';
            }
        });
        
        if (visibleSections === 0 && searchTerm.length > 0) {
            sections.forEach(section => {
                section.style.display = 'block';
            });
            
            highlightSearchMatches(searchTerm);
        } else {
            removeSearchHighlights();
        }
    });
}

function highlightSearchMatches(searchTerm) {
    const textElements = document.querySelectorAll('p, li, h2, h3, h4');
    
    textElements.forEach(element => {
        const originalHTML = element.innerHTML;
        const text = element.textContent;
        const regex = new RegExp(searchTerm, 'gi');
        
        if (regex.test(text)) {
            element.innerHTML = text.replace(regex, match => 
                `<span class="search-highlight">${match}</span>`
            );
        }
    });
    
    const style = document.createElement('style');
    style.textContent = `
        .search-highlight {
            background-color: #ffeb3b;
            color: #000;
            padding: 0 2px;
            border-radius: 2px;
            font-weight: bold;
        }
    `;
    document.head.appendChild(style);
}

function removeSearchHighlights() {
    const highlightedElements = document.querySelectorAll('.search-highlight');
    highlightedElements.forEach(element => {
        const parent = element.parentNode;
        parent.replaceChild(document.createTextNode(element.textContent), element);
        parent.normalize();
    });
}

function addLanguageAttributes() {
    const codeBlocks = document.querySelectorAll('.code-block');
    
    codeBlocks.forEach(block => {
        const pre = block.querySelector('pre');
        const code = pre.querySelector('code');
        
        if (code) {
            const language = code.className || 'cpp';
            block.setAttribute('data-language', language);
        } else {
            block.setAttribute('data-language', 'cpp');
        }
    });
}

function setupTooltips() {
    const codeElements = document.querySelectorAll('.code-block .type, .code-block .function');
    
    codeElements.forEach(element => {
        const tooltip = document.createElement('span');
        tooltip.className = 'tooltiptext';
        
        if (element.classList.contains('type')) {
            tooltip.textContent = 'Type: ' + element.textContent;
        } else if (element.classList.contains('function')) {
            tooltip.textContent = 'Function: ' + element.textContent;
        }
        
        const tooltipWrapper = document.createElement('span');
        tooltipWrapper.className = 'tooltip';
        tooltipWrapper.appendChild(element.cloneNode(true));
        tooltipWrapper.appendChild(tooltip);
        
        element.parentNode.replaceChild(tooltipWrapper, element);
    });
}

function setupCopyButtons() {
    const codeBlocks = document.querySelectorAll('.code-block');
    
    codeBlocks.forEach(block => {
        const copyButton = document.createElement('button');
        copyButton.className = 'copy-button';
        copyButton.innerHTML = 'Copy';
        copyButton.title = 'Copy code to clipboard';
        
        copyButton.addEventListener('click', function() {
            const code = block.querySelector('pre').textContent;
            navigator.clipboard.writeText(code).then(function() {
                copyButton.innerHTML = 'Copied!';
                copyButton.style.backgroundColor = '#4CAF50';
                
                setTimeout(function() {
                    copyButton.innerHTML = 'Copy';
                    copyButton.style.backgroundColor = '';
                }, 2000);
            });
        });
        
        block.appendChild(copyButton);
    });
    const style = document.createElement('style');
    style.textContent = `
        .copy-button {
            position: absolute;
            top: 10px;
            right: 10px;
            padding: 5px 10px;
            background-color: var(--primary-color);
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 0.8rem;
            transition: all 0.3s ease;
            z-index: 10;
        }
        
        .copy-button:hover {
            background-color: var(--secondary-color);
            transform: scale(1.05);
        }
    `;
    document.head.appendChild(style);
}
document.addEventListener('DOMContentLoaded', setupCopyButtons);