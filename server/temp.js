
        async function fetchStatus() {
            try {
                const res = await fetch('/api/status');
                const data = await res.json();
                document.getElementById('uptime').innerText = formatUptime(data.uptime);
                document.getElementById('online-count').innerText = 'Online: ' + data.online_count + ' Players';
                document.getElementById('exp-rate').value = data.exp_multiplier;
                document.getElementById('gold-rate').value = data.gold_multiplier;
            } catch(e) {
                console.error("Error fetching status", e);
            }
        }

        async function fetchPlayers() {
            try {
                const res = await fetch('/api/players');
                const players = await res.json();
                const tbody = document.getElementById('players-list');
                tbody.innerHTML = '';
                if(players.length === 0) {
                    tbody.innerHTML = '<tr><td colspan=\"7\" style=\"text-align: center; color: var(--text-muted);\">No players currently online.</td></tr>';
                    return;
                }
                players.forEach(p => {
                    const tr = document.createElement('tr');
                    tr.innerHTML = `
                        <td><strong>${p.name}</strong></td>
                        <td><span class="badge badge-cyan">Lv.${p.level}</span></td>
                        <td>🪙 ${p.gold}</td>
                        <td>🗺️ ${p.map_id}</td>
                        <td>${p.x}, ${p.y}</td>
                        <td>${p.ip}</td>
                        <td class="player-actions">
                            <button onclick="openWarpModal('${p.name}')">Teleport</button>
                            <button onclick="openLevelModal('${p.name}', ${p.level})">Level</button>
                            <button onclick="openGoldModal('${p.name}', ${p.gold})">Gold</button>
                            <button onclick="openItemModal('${p.name}')">Item</button>
                            <button onclick="openPetModal('${p.name}')">Pet</button>
                            <button style="background:linear-gradient(135deg,#667eea,#764ba2);" onclick="openDetailModal('${p.name}')">&#128203; Details</button>
                            <button class="btn-danger" onclick="kickPlayer('${p.name}')">Kick</button>
                        </td>
                    `;
                    tbody.appendChild(tr);
                });
            } catch(e) {
                console.error("Error fetching players", e);
            }
        }

        async function fetchLogs() {
            try {
                const res = await fetch('/api/logs');
                const logs = await res.json();
                const consoleDiv = document.getElementById('console');
                const isScrolledToBottom = consoleDiv.scrollHeight - consoleDiv.clientHeight <= consoleDiv.scrollTop + 1;
                
                consoleDiv.innerHTML = '';
                logs.forEach(line => {
                    const div = document.createElement('div');
                    div.className = 'console-line';
                    if (line.includes('[INFO]')) div.classList.add('info');
                    else if (line.includes('[WARNING]')) div.classList.add('warning');
                    else if (line.includes('[ERROR]') || line.includes('[CRITICAL]')) div.classList.add('error');
                    div.innerText = line;
                    consoleDiv.appendChild(div);
                });

                if (isScrolledToBottom) {
                    consoleDiv.scrollTop = consoleDiv.scrollHeight;
                }
            } catch(e) {
                console.error("Error fetching logs", e);
            }
        }

        async function updateConfig() {
            const exp = parseFloat(document.getElementById('exp-rate').value);
            const gold = parseFloat(document.getElementById('gold-rate').value);
            try {
                await fetch('/api/config', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({exp_multiplier: exp, gold_multiplier: gold})
                });
                alert("Multipliers updated successfully!");
                fetchStatus();
            } catch(e) {
                alert("Failed to update config.");
            }
        }

        async function sendBroadcast() {
            const input = document.getElementById('broadcast-msg');
            const msg = input.value;
            if(!msg) return;
            try {
                await fetch('/api/broadcast', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({message: msg})
                });
                input.value = '';
                alert("Announcement broadcasted!");
            } catch(e) {
                alert("Failed to broadcast.");
            }
        }

        async function kickPlayer(name) {
            if(!confirm("Are you sure you want to kick " + name + "?")) return;
            try {
                await fetch('/api/players/kick', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({name: name})
                });
                fetchPlayers();
            } catch(e) {
                alert("Failed to kick player.");
            }
        }

        // Warp Modal Controls
        function openWarpModal(name) {
            document.getElementById('warp-player-name').value = name;
            document.getElementById('warp-preset').value = '';
            document.getElementById('warp-modal').style.display = 'flex';
        }
        function onPresetMapChange() {
            const select = document.getElementById('warp-preset');
            const val = select.value;
            if (!val) return;
            const parts = val.split(',');
            document.getElementById('warp-map').value = parts[0];
            document.getElementById('warp-x').value = parts[1];
            document.getElementById('warp-y').value = parts[2];
        }
        function closeWarpModal() {
            document.getElementById('warp-modal').style.display = 'none';
        }
        async function confirmWarp() {
            const name = document.getElementById('warp-player-name').value;
            const map = parseInt(document.getElementById('warp-map').value);
            const x = parseInt(document.getElementById('warp-x').value);
            const y = parseInt(document.getElementById('warp-y').value);
            try {
                await fetch('/api/players/warp', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({name: name, map_id: map, x: x, y: y})
                });
                closeWarpModal();
                fetchPlayers();
            } catch(e) {
                alert("Failed to teleport player.");
            }
        }

        // Gold Modal Controls
        function openGoldModal(name, currentGold) {
            document.getElementById('gold-player-name').value = name;
            document.getElementById('gold-amt').value = currentGold + 1000;
            document.getElementById('gold-modal').style.display = 'flex';
        }
        function closeGoldModal() {
            document.getElementById('gold-modal').style.display = 'none';
        }
        async function confirmGold() {
            const name = document.getElementById('gold-player-name').value;
            const gold = parseInt(document.getElementById('gold-amt').value);
            try {
                await fetch('/api/players/gold', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({name: name, gold: gold})
                });
                closeGoldModal();
                fetchPlayers();
            } catch(e) {
                alert("Failed to set player gold.");
            }
        }

        // Level Modal Controls
        function openLevelModal(name, currentLevel) {
            document.getElementById('level-player-name').value = name;
            document.getElementById('level-val').value = currentLevel;
            document.getElementById('level-modal').style.display = 'flex';
        }
        function closeLevelModal() {
            document.getElementById('level-modal').style.display = 'none';
        }
        async function confirmLevel() {
            const name = document.getElementById('level-player-name').value;
            const level = parseInt(document.getElementById('level-val').value);
            try {
                await fetch('/api/players/level', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({name: name, level: level})
                });
                closeLevelModal();
                fetchPlayers();
            } catch(e) {
                alert("Failed to set player level.");
            }
        }

        // Item Modal Controls
        function openItemModal(name) {
            document.getElementById('item-player-name').value = name;
            document.getElementById('item-id-search').value = '';
            document.getElementById('item-amt').value = '1';
            document.getElementById('item-modal').style.display = 'flex';
        }function closeItemModal() {
            document.getElementById('item-modal').style.display = 'none';
        }
        async function confirmItem() {
            const name = document.getElementById('item-player-name').value;
            const val = document.getElementById('item-id-search').value;
    const itemId = parseInt(val.split(' ')[0]);
    if (isNaN(itemId)) { alert('Invalid Item ID'); return; }
            const amount = parseInt(document.getElementById('item-amt').value);
            try {
                const res = await fetch('/api/players/item', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({name: name, item_id: itemId, amount: amount})
                });
                const data = await res.json();
                if (data.status === "success") {
                    closeItemModal();
                    alert("Item given successfully!");
                } else {
                    alert("Error: " + data.message);
                }
            } catch(e) {
                alert("Failed to give item.");
            }
        }

        // Pet Modal Controls
        function openPetModal(name) {
            document.getElementById('pet-player-name').value = name;
            document.getElementById('pet-id-search').value = '';
            document.getElementById('pet-lvl').value = '1';
            document.getElementById('pet-modal').style.display = 'flex';
        }function closePetModal() {
            document.getElementById('pet-modal').style.display = 'none';
        }
        async function confirmPet() {
            const name = document.getElementById('pet-player-name').value;
            const val = document.getElementById('pet-id-search').value;
    const petId = parseInt(val.split(' ')[0]);
    if (isNaN(petId)) { alert('Invalid Pet ID'); return; }
            const level = parseInt(document.getElementById('pet-lvl').value);
            try {
                const res = await fetch('/api/players/pet', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({name: name, pet_id: petId, level: level})
                });
                const data = await res.json();
                if (data.status === "success") {
                    closePetModal();
                    alert("Pet given successfully!");
                } else {
                    alert("Error: " + data.message);
                }
            } catch(e) {
                alert("Failed to give pet.");
            }
        }

        // ── Player Detail Modal ────────────────────────────────────────────
        let _detailPlayerName = '';
        let _detailData = null;

        async function openDetailModal(name) {
            _detailPlayerName = name;
            document.getElementById('detail-modal-title').textContent = '👤 ' + name + ' — Player Details';
            document.getElementById('detail-modal').style.display = 'flex';
            switchDetailTab('items');
            await refreshDetailData();
        }

        function closeDetailModal() {
            document.getElementById('detail-modal').style.display = 'none';
        }

        function switchDetailTab(tab) {
            document.querySelectorAll('.detail-tab').forEach((t,i) => {
                t.classList.toggle('active', (i===0 && tab==='items') || (i===1 && tab==='pets'));
            });
            document.getElementById('detail-items-section').classList.toggle('active', tab==='items');
            document.getElementById('detail-pets-section').classList.toggle('active', tab==='pets');
        }

        async function refreshDetailData() {
            try {
                const res = await fetch('/api/players/details?name=' + encodeURIComponent(_detailPlayerName));
                if (!res.ok) { alert('Player not found or offline.'); return; }
                _detailData = await res.json();
                renderDetailItems(_detailData.items || []);
                renderDetailPets(_detailData.pets || []);
            } catch(e) { alert('Failed to load player details.'); }
        }

        function renderDetailItems(items) {
            const tbody = document.getElementById('detail-items-body');
            if (!items.length) { tbody.innerHTML = '<tr><td colspan="4" class="empty-msg">No items in inventory.</td></tr>'; return; }
            tbody.innerHTML = items.map((it, i) => `
                <tr>
                    <td>${i+1}</td>
                    <td><span class="badge badge-cyan">${it.item_id}</span></td>
                    <td>${it.amount || 1}</td>
                    <td><button class="btn-xs btn-sm-danger" onclick="adminDeleteItem(${it.slot})">🗑 Delete</button></td>
                </tr>
            `).join('');
        }

        function renderDetailPets(pets) {
            const tbody = document.getElementById('detail-pets-body');
            if (!pets.length) { tbody.innerHTML = '<tr><td colspan="7" class="empty-msg">No pets.</td></tr>'; return; }
            tbody.innerHTML = pets.map((p, i) => `
                <tr>
                    <td>${i+1}</td>
                    <td><span class="badge badge-cyan">${p.pet_id}</span></td>
                    <td><input class="lvl-input" id="pet-lvl-input-${i}" type="number" min="1" max="199" value="${p.level}"> <button class="btn-xs btn-teal" onclick="adminSetPetLevel(${i})">✓</button></td>
                    <td>${p.exp || 0}</td>
                    <td>${p.amity || 100}</td>
                    <td style="font-size:0.78rem;">${p.str||5}/${p.con||5}/${p.agi||5}/${p.int||5}/${p.wis||5}</td>
                    <td><button class="btn-xs btn-sm-danger" onclick="adminDeletePet(${i})">🗑 Delete</button></td>
                </tr>
            `).join('');
        }

        async function adminDeleteItem(slot) {
            if (!confirm(`Delete item at inventory slot ${slot}?`)) return;
            const res = await fetch('/api/players/delete_item', {
                method: 'POST', headers: {'Content-Type':'application/json'},
                body: JSON.stringify({name: _detailPlayerName, slot: slot})
            });
            const data = await res.json();
            if (data.status === 'success') { await refreshDetailData(); }
            else alert('Error: ' + data.message);
        }

        async function adminDeletePet(idx) {
            if (!confirm(`Delete pet at slot ${idx+1}?`)) return;
            const res = await fetch('/api/players/delete_pet', {
                method: 'POST', headers: {'Content-Type':'application/json'},
                body: JSON.stringify({name: _detailPlayerName, slot: idx+1})
            });
            const data = await res.json();
            if (data.status === 'success') { await refreshDetailData(); }
            else alert('Error: ' + data.message);
        }

        async function adminSetPetLevel(idx) {
            const newLevel = parseInt(document.getElementById(`pet-lvl-input-${idx}`).value);
            if (isNaN(newLevel) || newLevel < 1 || newLevel > 199) { alert('Level must be 1-199.'); return; }
            const res = await fetch('/api/players/pet_level', {
                method: 'POST', headers: {'Content-Type':'application/json'},
                body: JSON.stringify({name: _detailPlayerName, slot: idx+1, level: newLevel})
            });
            const data = await res.json();
            if (data.status === 'success') { await refreshDetailData(); alert(`Pet level set to ${newLevel}!`); }
            else alert('Error: ' + data.message);
        }
        // ──────────────────────────────────────────────────────────────────

        function formatUptime(secs) {
            const h = Math.floor(secs / 3600);
            const m = Math.floor((secs % 3600) / 60);
            const s = Math.floor(secs % 60);
            return `${h}h ${m}m ${s}s`;
        }

        async function fetchUsers() {
            try {
                const res = await fetch('/api/users');
                const users = await res.json();
                const tbody = document.getElementById('users-list');
                tbody.innerHTML = '';
                
                users.forEach(user => {
                    const tr = document.createElement('tr');
                    tr.innerHTML = `
                        <td>${user.id}</td>
                        <td style="font-weight: 600; color: var(--accent-cyan);">${user.username}</td>
                        <td>
                            <button class="btn-danger" style="padding: 0.4rem 0.8rem; font-size: 0.8rem;" onclick="deleteUser(${user.id}, '${user.username}')">Delete / Sil</button>
                        </td>
                    `;
                    tbody.appendChild(tr);
                });
            } catch(e) {
                console.error("Failed to fetch users", e);
            }
        }

        async function deleteUser(userId, username) {
            if(!confirm(`Are you sure you want to delete the user "${username}" (ID: ${userId})? This will also delete all their characters!`)) {
                return;
            }
            try {
                const res = await fetch('/api/users/delete', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({user_id: userId})
                });
                const data = await res.json();
                if(data.status === 'success') {
                    fetchUsers();
                    fetchPlayers();
                } else {
                    alert("Error: " + data.message);
                }
            } catch(e) {
                alert("Failed to delete user.");
            }
        }

        // Auto-refresh loops
        fetchStatus();
        fetchPlayers();
        fetchLogs();
        fetchUsers();
        setInterval(fetchStatus, 3000);
        setInterval(fetchPlayers, 2000);
        setInterval(fetchLogs, 1000);
        setInterval(fetchUsers, 5000);

        // Database Browser / Editor JS Logic
        let dbCurrentTable = '';
        let dbColumns = [];
        let dbPrimaryKey = '';
        let dbCurrentPage = 1;
        let dbPageLimit = 20;
        let dbSearch = '';
        let dbEditMode = 'add';
        let dbEditRowData = null;
        let dbTotalRows = 0;
        let dbRows = [];

        async function loadDbTables() {
            try {
                const res = await fetch('/api/db/tables');
                const tables = await res.json();
                const select = document.getElementById('db-table-select');
                select.innerHTML = '';
                tables.forEach(table => {
                    const option = document.createElement('option');
                    option.value = table;
                    option.textContent = table;
                    select.appendChild(option);
                });
                if (tables.length > 0) {
                    dbCurrentTable = tables[0];
                    loadDbTableData();
                }
            } catch (e) {
                console.error("Failed to load DB tables", e);
            }
        }

        async function loadDbTableData() {
            if (!dbCurrentTable) return;
            try {
                const url = `/api/db/query?table=${dbCurrentTable}&page=${dbCurrentPage}&limit=${dbPageLimit}&search=${encodeURIComponent(dbSearch)}`;
                const res = await fetch(url);
                const data = await res.json();
                
                dbColumns = data.columns || [];
                dbPrimaryKey = data.pk || '';
                dbRows = data.rows || [];
                dbTotalRows = data.total || 0;

                // Render Header
                const thead = document.getElementById('db-table-header');
                thead.innerHTML = '';
                const headerTr = document.createElement('tr');
                dbColumns.forEach(col => {
                    const th = document.createElement('th');
                    th.textContent = col;
                    headerTr.appendChild(th);
                });
                const thActions = document.createElement('th');
                thActions.textContent = 'Actions';
                headerTr.appendChild(thActions);
                thead.appendChild(headerTr);

                // Render Body
                const tbody = document.getElementById('db-table-body');
                tbody.innerHTML = '';
                if (dbRows.length === 0) {
                    const tr = document.createElement('tr');
                    const td = document.createElement('td');
                    td.colSpan = dbColumns.length + 1;
                    td.textContent = 'No records found';
                    td.style.textAlign = 'center';
                    tr.appendChild(td);
                    tbody.appendChild(tr);
                } else {
                    dbRows.forEach((row, idx) => {
                        const tr = document.createElement('tr');
                        dbColumns.forEach(col => {
                            const td = document.createElement('td');
                            td.textContent = row[col] !== null ? row[col] : 'NULL';
                            tr.appendChild(td);
                        });
                        const tdActions = document.createElement('td');
                        tdActions.innerHTML = `
                            <button onclick="openEditRowModal(${idx})" class="btn-success" style="padding: 0.2rem 0.5rem; font-size: 0.8rem; margin-right: 0.25rem;">Edit</button>
                            <button onclick="deleteDbRow(${idx})" class="btn-danger" style="padding: 0.2rem 0.5rem; font-size: 0.8rem;">Delete</button>
                        `;
                        tr.appendChild(tdActions);
                        tbody.appendChild(tr);
                    });
                }

                // Update Pagination Info
                const start = dbTotalRows === 0 ? 0 : (dbCurrentPage - 1) * dbPageLimit + 1;
                const end = Math.min(dbCurrentPage * dbPageLimit, dbTotalRows);
                document.getElementById('db-pagination-info').textContent = `Showing ${start} to ${end} of ${dbTotalRows} entries`;
                
                document.getElementById('db-prev-btn').disabled = dbCurrentPage <= 1;
                document.getElementById('db-next-btn').disabled = end >= dbTotalRows;
            } catch (e) {
                console.error("Failed to load table data", e);
            }
        }

        function changeTable() {
            dbCurrentTable = document.getElementById('db-table-select').value;
            dbCurrentPage = 1;
            dbSearch = '';
            document.getElementById('db-search-input').value = '';
            loadDbTableData();
        }

        let dbSearchTimeout;
        function searchTable() {
            clearTimeout(dbSearchTimeout);
            dbSearchTimeout = setTimeout(() => {
                dbSearch = document.getElementById('db-search-input').value.trim();
                dbCurrentPage = 1;
                loadDbTableData();
            }, 300);
        }

        function prevPage() {
            if (dbCurrentPage > 1) {
                dbCurrentPage--;
                loadDbTableData();
            }
        }

        function nextPage() {
            const end = dbCurrentPage * dbPageLimit;
            if (end < dbTotalRows) {
                dbCurrentPage++;
                loadDbTableData();
            }
        }

        function openAddRowModal() {
            dbEditMode = 'add';
            dbEditRowData = null;
            document.getElementById('db-edit-modal-title').textContent = `Add New Row to ${dbCurrentTable}`;
            const form = document.getElementById('db-edit-form');
            form.innerHTML = '';
            
            dbColumns.forEach(col => {
                const group = document.createElement('div');
                group.className = 'form-group';
                
                const label = document.createElement('label');
                label.textContent = col;
                
                const input = document.createElement('input');
                input.type = 'text';
                input.id = `db-input-${col}`;
                input.placeholder = col === dbPrimaryKey ? 'Autogenerated if integer' : `Enter ${col}`;
                
                group.appendChild(label);
                group.appendChild(input);
                form.appendChild(group);
            });
            
            document.getElementById('db-edit-modal').style.display = 'flex';
        }

        function openEditRowModal(rowIndex) {
            dbEditMode = 'edit';
            dbEditRowData = dbRows[rowIndex];
            document.getElementById('db-edit-modal-title').textContent = `Edit Row in ${dbCurrentTable}`;
            const form = document.getElementById('db-edit-form');
            form.innerHTML = '';
            
            dbColumns.forEach(col => {
                const group = document.createElement('div');
                group.className = 'form-group';
                
                const label = document.createElement('label');
                label.textContent = col;
                
                const input = document.createElement('input');
                input.type = 'text';
                input.id = `db-input-${col}`;
                input.value = dbEditRowData[col] !== null ? dbEditRowData[col] : '';
                if (col === dbPrimaryKey) {
                    input.disabled = true;
                    input.style.opacity = '0.5';
                }
                
                group.appendChild(label);
                group.appendChild(input);
                form.appendChild(group);
            });
            
            document.getElementById('db-edit-modal').style.display = 'flex';
        }

        function closeDbEditModal() {
            document.getElementById('db-edit-modal').style.display = 'none';
        }

        async function saveDbRow() {
            const rowData = {};
            dbColumns.forEach(col => {
                const val = document.getElementById(`db-input-${col}`).value.trim();
                if (dbEditMode === 'add' && col === dbPrimaryKey && val === '') {
                    return;
                }
                rowData[col] = val === '' ? null : val;
            });

            try {
                let url = '';
                let payload = {};
                if (dbEditMode === 'edit') {
                    url = '/api/db/update';
                    payload = {
                        table: dbCurrentTable,
                        pk_col: dbPrimaryKey,
                        pk_val: dbEditRowData[dbPrimaryKey],
                        row_data: rowData
                    };
                } else {
                    url = '/api/db/insert';
                    payload = {
                        table: dbCurrentTable,
                        row_data: rowData
                    };
                }

                const res = await fetch(url, {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify(payload)
                });
                const data = await res.json();
                if (data.status === 'success') {
                    closeDbEditModal();
                    loadDbTableData();
                } else {
                    alert("Error: " + data.message);
                }
            } catch (e) {
                alert("Failed to save database row.");
            }
        }

        async function deleteDbRow(rowIndex) {
            const row = dbRows[rowIndex];
            const pkVal = row[dbPrimaryKey];
            if (!confirm(`Are you sure you want to delete this row from ${dbCurrentTable} where ${dbPrimaryKey} = ${pkVal}?`)) {
                return;
            }
            try {
                const res = await fetch('/api/db/delete', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/json'},
                    body: JSON.stringify({
                        table: dbCurrentTable,
                        pk_col: dbPrimaryKey,
                        pk_val: pkVal
                    })
                });
                const data = await res.json();
                if (data.status === 'success') {
                    loadDbTableData();
                } else {
                    alert("Error: " + data.message);
                }
            } catch (e) {
                alert("Failed to delete database row.");
            }
        }

        // Initialize DB tables dropdown
        loadDbTables();
    