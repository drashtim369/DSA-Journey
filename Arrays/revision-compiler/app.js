const state = { currentIndex: 0, filter: 'All', editor: null };

const els = {
  questionList: document.getElementById('questionList'),
  qTitle: document.getElementById('qTitle'),
  qDifficulty: document.getElementById('qDifficulty'),
  qLink: document.getElementById('qLink'),
  qPrompt: document.getElementById('qPrompt'),
  qInputFormat: document.getElementById('qInputFormat'),
  sampleInput: document.getElementById('sampleInput'),
  expectedOutput: document.getElementById('expectedOutput'),
  yourOutput: document.getElementById('yourOutput'),
  statusBox: document.getElementById('statusBox'),
  runBtn: document.getElementById('runBtn'),
  submitBtn: document.getElementById('submitBtn'),
  resetBtn: document.getElementById('resetBtn'),
  nextBtn: document.getElementById('nextBtn')
};

function filteredQuestions() {
  return state.filter === 'All' ? QUESTIONS : QUESTIONS.filter(q => q.difficulty === state.filter);
}

function getCurrentQuestion() {
  return filteredQuestions()[state.currentIndex] || filteredQuestions()[0];
}

function normalize(text) {
  return text.trim().replace(/\r/g, '').split('\n').map(line => line.trim()).join('\n');
}

function renderList() {
  const items = filteredQuestions();
  els.questionList.innerHTML = '';
  items.forEach((q, idx) => {
    const li = document.createElement('li');
    li.textContent = `${q.id}. ${q.title}`;
    li.className = idx === state.currentIndex ? 'active' : '';
    li.onclick = () => {
      state.currentIndex = idx;
      loadQuestion();
    };
    els.questionList.appendChild(li);
  });
}

function loadQuestion() {
  const q = getCurrentQuestion();
  if (!q) return;
  els.qTitle.textContent = `${q.id}. ${q.title}`;
  els.qDifficulty.textContent = q.difficulty;
  els.qLink.href = q.url;
  els.qPrompt.textContent = q.prompt;
  els.qInputFormat.textContent = q.inputFormat;
  els.sampleInput.value = q.tests[0].input;
  els.expectedOutput.value = q.tests[0].output;
  els.yourOutput.value = '';
  els.statusBox.value = 'Write your solution and click Submit.';
  if (state.editor) state.editor.setValue(q.starter);
  renderList();
}

async function runCode() {
  const q = getCurrentQuestion();
  const code = state.editor.getValue();
  els.statusBox.value = 'Running on sample test...';
  try {
    const res = await fetch('https://emkc.org/api/v2/piston/execute', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        language: 'cpp',
        version: '10.2.0',
        files: [{ content: code }],
        stdin: q.tests[0].input
      })
    });
    const data = await res.json();
    els.yourOutput.value = data.run?.output || data.run?.stderr || 'No output';
    els.statusBox.value = data.run?.code === 0 ? 'Run complete.' : `Runtime/Compile issue (code ${data.run?.code ?? 'N/A'})`;
    return data.run?.output || '';
  } catch (err) {
    els.statusBox.value = `Execution error: ${err.message}`;
    return '';
  }
}

async function submitCode() {
  const q = getCurrentQuestion();
  els.statusBox.value = 'Submitting... running all tests';
  for (let i = 0; i < q.tests.length; i++) {
    const test = q.tests[i];
    const res = await fetch('https://emkc.org/api/v2/piston/execute', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        language: 'cpp',
        version: '10.2.0',
        files: [{ content: state.editor.getValue() }],
        stdin: test.input
      })
    });
    const data = await res.json();
    const out = normalize(data.run?.output || '');
    if ((data.run?.code ?? 1) !== 0) {
      els.statusBox.value = `❌ Failed: compile/runtime error on test ${i + 1}`;
      els.yourOutput.value = data.run?.stderr || data.run?.output || 'Error';
      return;
    }
    if (out !== normalize(test.output)) {
      els.statusBox.value = `❌ Wrong Answer on test ${i + 1}`;
      els.yourOutput.value = data.run?.output || '';
      return;
    }
  }
  els.statusBox.value = '✅ Accepted! You can move to next question.';
}

function initMonaco() {
  require.config({ paths: { vs: 'https://cdn.jsdelivr.net/npm/monaco-editor@0.45.0/min/vs' } });
  require(['vs/editor/editor.main'], () => {
    monaco.languages.registerCompletionItemProvider('cpp', {
      provideCompletionItems: () => ({
        suggestions: [
          {
            label: 'cp-template',
            kind: monaco.languages.CompletionItemKind.Snippet,
            insertText: '#include <bits/stdc++.h>\nusing namespace std;\n\nint main(){\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n    ${1:// code}\n    return 0;\n}',
            insertTextRules: monaco.languages.CompletionItemInsertTextRule.InsertAsSnippet,
            documentation: 'Fast C++ template'
          }
        ]
      })
    });

    state.editor = monaco.editor.create(document.getElementById('editor'), {
      value: QUESTIONS[0].starter,
      language: 'cpp',
      theme: 'vs-dark',
      automaticLayout: true,
      minimap: { enabled: false },
      fontSize: 14,
      tabSize: 2,
      autoClosingBrackets: 'always',
      suggestOnTriggerCharacters: true,
      quickSuggestions: true
    });

    loadQuestion();
  });
}

document.querySelectorAll('.filters button').forEach(btn => {
  btn.onclick = () => {
    document.querySelectorAll('.filters button').forEach(b => b.classList.remove('active'));
    btn.classList.add('active');
    state.filter = btn.dataset.filter;
    state.currentIndex = 0;
    loadQuestion();
  };
});

els.runBtn.onclick = runCode;
els.submitBtn.onclick = submitCode;
els.resetBtn.onclick = () => {
  const q = getCurrentQuestion();
  state.editor.setValue(q.starter);
};
els.nextBtn.onclick = () => {
  const list = filteredQuestions();
  state.currentIndex = (state.currentIndex + 1) % list.length;
  loadQuestion();
};

initMonaco();
